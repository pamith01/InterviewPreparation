#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define RING_SIZE 16  // must be power of 2
#define MASK      (RING_SIZE - 1)
#define NUM_ITEMS 25

typedef struct {
    int data[RING_SIZE];
    atomic_uint head;  // consumer reads from here
    atomic_uint tail;  // producer writes to here
} spsc_ring_t;

void spsc_init(spsc_ring_t* r) {
    atomic_init(&r->head, 0);
    atomic_init(&r->tail, 0);
}

// Producer only — no lock needed
bool spsc_push(spsc_ring_t* r, int item) {
    uint32_t tail = atomic_load_explicit(&r->tail, memory_order_relaxed);
    uint32_t next = (tail + 1) & MASK;

    // Full check: read head with acquire to sync with consumer
    if (next == atomic_load_explicit(&r->head, memory_order_acquire))
        return false;  // full

    r->data[tail] = item;

    // Publish: release so consumer sees data before tail update
    atomic_store_explicit(&r->tail, next, memory_order_release);
    return true;
}

// Consumer only — no lock needed
bool spsc_pop(spsc_ring_t* r, int* item) {
    uint32_t head = atomic_load_explicit(&r->head, memory_order_relaxed);

    // Empty check: read tail with acquire
    if (head == atomic_load_explicit(&r->tail, memory_order_acquire))
        return false;  // empty

    *item = r->data[head];

    // Advance: release so producer sees updated head
    atomic_store_explicit(&r->head, (head + 1) & MASK, memory_order_release);
    return true;
}

typedef struct {
    spsc_ring_t* ring;
    atomic_bool done;
} demo_ctx_t;

void* producer_fn(void* arg) {
    demo_ctx_t* ctx = (demo_ctx_t*)arg;
    int produced = 0;

    while (produced < NUM_ITEMS) {
        int val = 100 + produced;
        if (spsc_push(ctx->ring, val)) {
            printf("[Producer] pushed %d\n", val);
            produced++;
            usleep(100000);  // 100 ms
        } else {
            // Buffer full: spin/yield briefly without blocking on a mutex
            usleep(50000);
        }
    }

    atomic_store_explicit(&ctx->done, true, memory_order_release);
    return NULL;
}

void* consumer_fn(void* arg) {
    demo_ctx_t* ctx = (demo_ctx_t*)arg;
    int item = 0;

    while (1) {
        if (spsc_pop(ctx->ring, &item)) {
            printf("[Consumer] popped %d\n", item);
            usleep(180000);  // 180 ms (slightly slower than producer)
        } else if (atomic_load_explicit(&ctx->done, memory_order_acquire)) {
            // Drain any items pushed right before 'done' became true
            while (spsc_pop(ctx->ring, &item)) {
                printf("[Consumer] drained %d\n", item);
            }
            break;
        } else {
            usleep(50000);
        }
    }

    return NULL;
}

int main(void) {
    spsc_ring_t ring;
    spsc_init(&ring);

    demo_ctx_t ctx = {
        .ring = &ring,
        .done = ATOMIC_VAR_INIT(false)
    };

    pthread_t prod_tid, cons_tid;
    pthread_create(&prod_tid, NULL, producer_fn, &ctx);
    pthread_create(&cons_tid, NULL, consumer_fn, &ctx);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    printf("Done.\n");
    return 0;
}