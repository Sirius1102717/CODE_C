#include <ctype.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 30
#define PRODUCER_NUM 10
#define CONSUMER_NUM 5
#define SLEEP_TIME 100
#define EXIT_LIMIT 5

typedef __int64_t semaphore;

size_t buffer[BUFFER_SIZE] = { 0 };
size_t producer_count = 0;
size_t in = 0;
size_t out = 0;

semaphore mutex = 1, producer_mutex = 1;
size_t empty = BUFFER_SIZE, full = 0;

void* producer() {

    for(;;) {
        while(producer_mutex <= 0) {}

        producer_mutex--;
        printf("生产一个产品ID:%zu, 缓冲区位置:%zu\n", ++producer_count, in);
        producer_mutex++;

        size_t exit_num = 0;
        while(empty <= 0 && exit_num++ < EXIT_LIMIT) puts("缓冲区已满!");
        // while(empty <= 0) puts("缓冲区已满");
        empty--;

        time_t wait_time = 100;
        while(mutex <= 0) {
            if(wait_time <= 0) exit(1);
        }
        mutex--;
        buffer[in] = producer_count;
        in = (in + 1) % BUFFER_SIZE;
        mutex++;
        full++;
        sleep(SLEEP_TIME);
    }
}

void* consumer() {
    for(;;) {
        size_t exit_num = 0;
        while(full <= 0 && exit_num++ < EXIT_LIMIT) puts("缓冲区为空!");
        full--;
        time_t wait_time = 100;
        while(mutex <= 0) {
            if(wait_time <= 0) exit(1);
        }
        mutex--;

        size_t produce_num = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;

        mutex++;
        empty++;
        printf("消费一个产品ID:%zu,缓冲区位置:%zu\n", produce_num, out);
        sleep(SLEEP_TIME);
    }
}
int main(int argc, char* argv[]) {
    freopen("/home/sirius/CODE_C/input.txt", "r", stdin);
    // freopen("/home/sirius/CODE_C/output.txt", "w", stdout);

    pthread_t thread_pool[PRODUCER_NUM + CONSUMER_NUM];
    for(size_t i = 0; i < PRODUCER_NUM; i++) {
        pthread_t tmp;
        if(!~pthread_create(&tmp, NULL, producer, NULL)) {
            fprintf(stderr, "fail to create producer%zu\n", i);
            // return 1;
            exit(1);
        }
        thread_pool[i] = tmp;
    }
    for(size_t i = 0; i < CONSUMER_NUM; i++) {
        pthread_t tmp;
        if(!~pthread_create(&tmp, NULL, consumer, NULL)) {
            fprintf(stderr, "fail to create consumer%zu\n", i);
            // return 1;
            exit(1);
        }
        thread_pool[i + PRODUCER_NUM] = tmp;
    }

    for(size_t i = 0; i < CONSUMER_NUM + PRODUCER_NUM; i++) {
        if(!~pthread_join(thread_pool[i], NULL)) {
            fprintf(stderr, "fail to recollect\n");
            // return 1;
            exit(1);
        }
    }

    return 0;
}
