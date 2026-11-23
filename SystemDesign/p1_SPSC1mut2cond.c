/* Simple Producer Consumer Problem with 1 mutex and 2 condition variables */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

static int buffer[BUFFER_SIZE];
int count = 0;

void* producer(void* arg)
{
    int item = 0;
    while(1){
        pthread_mutex_lock(&lock);
        while(count == BUFFER_SIZE){
            pthread_cond_wait(&not_full, &lock);
        }
        buffer[count++] = item;
        printf("Produced: %d, count: %d\n", item++, count);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(count == 0){
            pthread_cond_wait(&not_empty, &lock);
        }
        int item = buffer[--count];
        printf("Consumed: %d, item: %d\n", item, count);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t pt, ct;
    pthread_create(&pt, NULL, producer, NULL);
    pthread_create(&ct, NULL, consumer, NULL);

    pthread_join(pt, NULL);
    pthread_join(ct, NULL);
    return 0;
}