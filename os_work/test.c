#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_THREADS 10
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

void* printf_hello_world(void* tid) {
    printf("Hello World %d.\n", tid);
    int* a = (int*)malloc(sizeof(int));
    *a = (int)tid * (int)tid;
    // pthread_exit(0);
    return a;
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;
    for(int i = 0; i < NUMBER_OF_THREADS; i++) {

        printf("Main here. Creating thread %d\n", i);
        status = pthread_create(&threads[i], NULL, printf_hello_world, (void*)i);
        int** res = (int**)malloc(sizeof(int*));
        pthread_join(threads[i], (void**)res);
        printf("res[%d]:%d\n", i, **res);
        if(status) {
            printf("pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }
    for(int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    exit(0);

    return 0;
}
