#include <pthread.h>
#include <stdio.h>

typedef struct {
    int a;
    int b;
    int c;
} S;

int main() {
    int arr[10] = { [1 ... 5] = 5 };
    for(int i = 0; i < 10; i++) 
        printf("%d\n", arr[i]);
    S s = { .a = 100, .b = 100, .c = 100 };
    printf("%p", &s);
}

