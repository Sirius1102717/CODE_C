#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)
#define ll long long
#define new(type) (type*)malloc(sizeof(type))
#define delete(type) free(type)
const double EPS = 1e-8;
const ll MAXN = 1e18;
const int INF = 0x3f3f3f3f;
void swap(void* a, void* b, int size) {
    void* c = new(void);
    memcpy(c, a, size), memcpy(a, b, size), memcpy(b, c, size), delete(c);
}
bool started = true;

pthread_mutex_t mutex;
pthread_cond_t cond;

void* f_pay(void* i) {
    pthread_mutex_lock(&mutex);
    while(!started) { pthread_cond_wait(&cond, &mutex); }
    printf("发工资%zu\n", (size_t)i);
    pthread_mutex_unlock(&mutex);
}

void* pay() {
    pthread_t thread_pool[50];

    for(size_t i = 0; i < 50; i++) {
        pthread_t tmp;
        pthread_create(&tmp, NULL, f_pay, (void*)i);
        thread_pool[i] = tmp;
    }
    for(int i = 0; i < 50; i++) pthread_join(thread_pool[i], NULL);
}
void* f_cal(void* i) {
    pthread_mutex_lock(&mutex);
    while(!started) { pthread_cond_wait(&cond, &mutex); }
    printf("计算利息%zu\n", (size_t)i);
    pthread_mutex_unlock(&mutex);
}

void* cal() {
    pthread_t thread_pool[50];

    for(size_t i = 0; i < 50; i++) {
        pthread_t tmp;
        pthread_create(&tmp, NULL, f_cal, (void*)i);
        thread_pool[i] = tmp;
    }
    for(int i = 0; i < 50; i++) pthread_join(thread_pool[i], NULL);
}

void* dep() {
    pthread_mutex_lock(&mutex);
    started = false;
    puts("存款");
    started = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
}
void* with() {
    pthread_mutex_lock(&mutex);
    started = false;
    puts("取款");
    started = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
}
void* tran() {
    pthread_mutex_lock(&mutex);
    started = false;
    puts("转账");
    started = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
}

int main(int argc, char* argv[]) {
    freopen("/home/sirius/CODE_C/input.txt", "r", stdin);
    freopen("/home/sirius/CODE_C/output.txt", "w", stdout);
    // fork();
    // pthread_t p_pay, p_dep, p_cal, p_with, p_tran;
    // pthread_mutex_init(&mutex, NULL);
    // pthread_cond_init(&cond, NULL);
    // pthread_create(&p_pay, NULL, pay, NULL);
    // pthread_create(&p_cal, NULL, cal, NULL);
    // pthread_create(&p_dep, NULL, dep, NULL);
    // pthread_create(&p_with, NULL, with, NULL);
    // pthread_create(&p_tran, NULL, tran, NULL);
    // pthread_join(p_pay, NULL);
    // sleep(5);
    key_t key = 0;

    return 0;
}
