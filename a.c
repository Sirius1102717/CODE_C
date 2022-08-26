#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<pthread.h>
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
    memcpy(c, a, size),memcpy(a, b, size),memcpy(b, c, size),delete(c);
}

int main(int argc, char *argv[]) {
    freopen("/home/sirius/CODE_C/input.txt", "r", stdin);
    freopen("/home/sirius/CODE_C/output.txt", "w", stdout);

    return 0; 
}


