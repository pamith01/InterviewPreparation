/* Classic bounded buffer problem with N Producers and N Consumers using 1 mutex and 2 conditon variables */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

static int buffer[BUFFER_SIZE];
int head=0, tail=0, count=0;

void enqueue(int item)
{
    buffer[tail] = item;
    tail = (tail+1)%BUFFER_SIZE;
    count++;
}

int dequeue(void)
{
    int item = buffer[head];
    head = (head+1)%BUFFER_SIZE;
    count--;
    return item;
}

void* producer(void* arg)
{
    int id = *(int *)arg;
    int item = id*100;
    while(1){
        pthread_mutex_lock(&lock);
        while(count == BUFFER_SIZE){
            pthread_cond_wait(&not_full, &lock);
        }
        enqueue(item);
        printf("[P%d] Produced: %d\n", id, item++);
        pthread_cond_broadcast(&not_empty);
        pthread_mutex_unlock(&lock);
        usleep(500000);
    }
    return NULL;

}

void* consumer(void* arg)
{
    int id = *(int *)arg;
    while(1){
        pthread_mutex_lock(&lock);
        while(count == 0){
            pthread_cond_wait(&not_empty, &lock);
        }
        int item = dequeue();
        printf("[C%d] Consumed: %d\n", id, item);
        pthread_cond_broadcast(&not_full);
        pthread_mutex_unlock(&lock);
        usleep(800000);
    }
    return NULL;
}

int main()
{
    pthread_t pt[NUM_PRODUCERS], ct[NUM_CONSUMERS];

    for (int i=0; i < NUM_PRODUCERS; i++){
        pthread_create(&pt[i], NULL, producer, &i);
        pthread_create(&ct[i], NULL, consumer, &i);
    }

    for (int i=0;i<NUM_CONSUMERS;i++){
        pthread_join(pt[i], NULL);
        pthread_join(ct[i], NULL);
    }
    return 0;
}