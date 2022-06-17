#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SIZE 13

#define EMPTY -1;

#define SLEEP_TIME 1

#define MAX_NUM 100

typedef __int64_t type;
typedef struct queue {
    type data[SIZE];
    type begin;
    type end;
} Queue;

struct data {
    sem_t empty;
    sem_t full;
    Queue q;
};

pthread_mutex_t mutex;

type num = 0;

struct data sem;

bool init(Queue* q) {
    if(!q) return false;
    q->begin = 0;
    q->end = 0;
    return true;
}

bool is_empty(Queue* q) {
    return q && q->begin == q->end;
}

bool is_full(Queue* q) {
    return q && q->begin == (q->end + 1) % SIZE;
}

type peek(Queue* q) {

    if(q) {
        q->begin = (q->begin + 1) % SIZE;
        return q->data[q->begin];
    }
    return EMPTY;
}

bool push(Queue* q, int x) {
    if(q && !is_full(q)) {
        q->end = (q->end + 1) % SIZE;
        q->data[q->end] = x;
        return true;
    }
    return false;
}

void* producer() {
    for(;;) {
        sleep(SLEEP_TIME);
        sem_wait(&sem.empty);
        pthread_mutex_lock(&mutex);
        num++;
        push(&sem.q, num);
        printf("生产了一条消息：%ld\n", num);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem.full);
    }
}
void* consumer() {
    for(;;) {
        sleep(SLEEP_TIME);
        sem_wait(&sem.full);
        pthread_mutex_lock(&mutex);
        num--;
        num = peek(&sem.q);
        puts("消费了一条消息");
        pthread_mutex_unlock(&mutex);
        sem_post(&sem.empty);
    }
}

int main() {
    srand(time(NULL));
    sem_init(&sem.empty, 0, 10);
    sem_init(&sem.full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    init(&sem.q);

    pthread_t producer_id;
    pthread_t consumer_id;

    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);

    pthread_join(consumer_id, NULL);
    sem_destroy(&sem.empty);
    sem_destroy(&sem.full);
    pthread_mutex_destroy(&mutex);
    return 0;
}