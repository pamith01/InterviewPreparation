#include <stdio.h>
#include <stdbool.h>

/* Simple Circular Buffer Implementation */

#define BUFFER_SIZE 5

typedef struct{
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} Circular_Buffer_t;

/* Initialize the buffer */
void Circular_Buffer_init(Circular_Buffer_t* cb){
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

/* Check if the buffer is full */
bool is_full(Circular_Buffer_t* cb){
    return (cb->count == BUFFER_SIZE);
}

/* Check if the buffer is empty */
bool is_empty(Circular_Buffer_t* cb){
    return (cb->count == 0);
}

/* Add an element to the buffer */
bool push(Circular_Buffer_t* cb, int item){
    if (is_full(cb))
        return false;
    
    cb->data[cb->tail] = item;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count++;
    return true;
}

bool pop(Circular_Buffer_t* cb, int* item){
    if (is_empty(cb))
        return false;
    
    *item = cb->data[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count--;
    return true;
}

int main()
{
    Circular_Buffer_t cb;
    Circular_Buffer_init(&cb);

    printf("Pushing 10, 20, 30...\n");
    push(&cb, 10);
    push(&cb, 20);
    push(&cb, 30);

    int val;
    while(!is_empty(&cb)){
        pop(&cb, &val);
        printf("Val popped: %d\n", val);
    }
    return 0;
}