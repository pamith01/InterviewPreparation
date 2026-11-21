#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

#define ITERS 200000
#define THREADS 4

static long plain_counter;
static long mutex_counter;
static long spin_counter;
static atomic_long atomic_counter;

static pthread_mutex_t mtx;
static pthread_spinlock_t spin; 

static void* worker(void* arg)
{
    for (int i=0;i < ITERS; i++)
    {
        pthread_mutex_lock(&mtx);
        mutex_counter++;
        pthread_mutex_unlock(&mtx);

        pthread_spin_lock(&spin);
        spin_counter++;
        pthread_spin_unlock(&spin);

        atomic_fetch_add_explicit(&atomic_counter, 1, memory_order_relaxed);
    }
    return NULL;
}

static void* racy_worker(void* arg)
{
    for (int i=0; i < ITERS; i++)
    {
        *(volatile long *)&plain_counter+=1;
    }
    return NULL;
}

int main()
{
    pthread_t t[THREADS], r[THREADS];
    
    pthread_mutex_init(&mtx, NULL);
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

    for (int i = 0; i < THREADS; i++){
        pthread_create(&t[i], NULL, worker, NULL);
        pthread_create(&r[i], NULL, racy_worker, NULL);
    }

    for (int i=0;i<THREADS;i++)
    {
        pthread_join(t[i], NULL);
        pthread_join(r[i], NULL);
    }

    printf("Expected value: %ld\n", (long)(THREADS*ITERS));
    printf("Mutex: %ld\n", mutex_counter);
    printf("Spinlock: %ld\n", spin_counter);
    printf("Atomic counter: %ld\n", atomic_counter);
    printf("Plain Counter: %ld\n", plain_counter);
    pthread_mutex_destroy(&mtx);
    pthread_spin_destroy(&spin);
    return 0;
}

