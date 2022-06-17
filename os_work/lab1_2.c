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

#define SLEEP_TIME 100000

#define SEM_VALUE 10

#define MAX_NUM 100

typedef __int64_t type;

pthread_mutex_t mutex;
type num = 0;

typedef struct queue {
    type buffer[SIZE];
    type begin;
    type end;
} Queue;

struct data {
    sem_t empty;
    sem_t full;
    Queue q;
};


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

    if(q && !is_empty(q)) {
        q->begin = (q->begin + 1) % SIZE;
        return q->buffer[q->begin];
    }
    return EMPTY;
}

bool push(Queue* q, int x) {
    if(q && !is_full(q)) {
        q->end = (q->end + 1) % SIZE;
        q->buffer[q->end] = x;
        return true;
    }
    return false;
}

void* producer() {
    for(;;) {
        int time = rand() % 10 + 1;
        usleep(SLEEP_TIME * time);
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
        int time = rand() % 10 + 1;
        usleep(SLEEP_TIME * time);
        sem_wait(&sem.full);
        pthread_mutex_lock(&mutex);
        num--;
        num = peek(&sem.q);
        puts("消费了一条消息");
        pthread_mutex_unlock(&mutex);
        sem_post(&sem.empty);
    }
}
void* do_operation() {
    pthread_t producer_id;
    pthread_t consumer_id;
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);

    pthread_join(consumer_id, NULL);
    // pthread_join(producer_id, NULL);
    // sleep(SLEEP_TIME * 100);
    // return NULL;
}

int main() {
    srand(time(NULL));
    sem_init(&sem.empty, 0, SEM_VALUE);
    sem_init(&sem.full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    init(&sem.q);

    // pthread_t producer_id;
    // pthread_t consumer_id;

    pthread_t operation;

    pthread_create(&operation, NULL, do_operation, NULL);

    // pthread_create(&producer_id, NULL, producer, NULL);
    // pthread_create(&consumer_id, NULL, consumer, NULL);

    // pthread_join(consumer_id, NULL);
    // pthread_join(producer_id, NULL);
    pthread_join(operation, NULL);
    sem_destroy(&sem.empty);
    sem_destroy(&sem.full);
    pthread_mutex_destroy(&mutex);
    return 0;
}