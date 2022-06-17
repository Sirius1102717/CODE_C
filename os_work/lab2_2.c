#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

typedef size_t type;
#define THREAD_NUM 5
type thread_num = 0;

typedef enum status { R, E } Status;

typedef struct pcb {
    char name[10];
    time_t need_time;
    time_t run_time;
    Status status;
    struct pcb* next;
} PCB;

PCB *begin, *end, *f_begin, *f_end;

time_t cpu_time = 0;

void init(PCB** p) {
    *p = new(PCB);
    (*p)->next = NULL;
    (*p)->status = R;
    (*p)->run_time = 0;
}

void push(PCB** rear, PCB* p) {
    (*rear)->next = p;
    *rear = p;
}

PCB* front(PCB** head) {
    PCB* p = *head;
    if(p) {
        *head = (*head)->next;
        p->next = NULL;
        return p;
    } else
        return NULL;
}

char* get_status(Status status) {
    switch(status) {
        case R: return "ready";
        case E: return "finish";
    }
}

void print(PCB* p, PCB* f_p) {
    while(p) {
        printf("name:%-*sneedtime:%-4ldruntime:%-4ld\tstatus:%-*s\n", 4,
               p->name, p->need_time, p->run_time, 4, get_status(p->status));
        p = p->next;
    }
    while(f_p) {
        printf("name:%-*sneedtime:%-4ldruntime:%-4ld\tstatus:%-*s\n", 4,
               f_p->name, f_p->need_time, f_p->run_time, 4,
               get_status(f_p->status));
        f_p = f_p->next;
    }
    puts("");
}

void run(PCB* head, PCB* rear, PCB* f_head, PCB* f_rear) {
    PCB* p = NULL;
    while(thread_num < THREAD_NUM) {
        print(head, f_head->next);
        cpu_time++;
        p = front(&head);
        if(p->need_time > 0) {
            p->run_time++;
            p->need_time--;
            if(0 == p->need_time) {
                p->status = E;
                push(&f_rear, p);
                thread_num++;
            } else {

                if(head)
                    push(&rear, p);
                else
                    head = p;
            }
        }
    }
    print(head, f_head->next);
}

void input() {

    char name[10];
    time_t need_time;
    init(&begin);
    end = begin;
    for(size_t i = 0; i < 5; i++) {
        scanf("%s%ld", name, &need_time);
        PCB* p;
        init(&p);
        strcpy(p->name, name);
        p->need_time = need_time;
        push(&end, p);
    }
}

int main(int argc, char* argv[]) {
    freopen("/home/sirius/CODE_C/input.txt", "r", stdin);
    freopen("/home/sirius/CODE_C/output.txt", "w", stdout);
    input();
    init(&f_begin);
    f_end = f_begin;
    printf("name\t needtime \t\t runtime \t\t status\n");
    run(begin->next, end, f_begin, f_end);

    return 0;
}
