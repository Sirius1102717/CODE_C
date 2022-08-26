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
const double EpS = 1e-8;
const ll MAXN = 1e18;
const int INF = 0x3f3f3f3f;
void swap(void* a, void* b, int size) {
    void* c = new(void);
    memcpy(c, a, size), memcpy(a, b, size), memcpy(b, c, size), delete(c);
}

typedef enum status { R, E, W } Status;

// typedef __int32_t int32_t;

typedef struct pcb {
    char name[10];
    int32_t priority;
    // time_t round;
    // time_t waiting;
    time_t need_time;
    // time_t run_time;
    Status status;
    struct pcb* next;
} PCB;

PCB *begin, *end, *f_begin, *f_end;

time_t cpu_time = 0;

void init(PCB** p) {
    *p = new(PCB);
    (*p)->next = NULL;
    (*p)->status = R;
    // (*p)->waiting = LONG_MAX;
    // (*p)->run_time = 0;
}

void push(PCB** rear, PCB* p) {
    PCB* cur = *rear;
    while(cur->next) {
        if(p->priority <= cur->priority && cur->next->priority < p->priority) {
            p->next = cur->next;
            cur->next = p;
            return;
        } else {
            cur = cur->next;
        }
    }
    cur->next = p;
}

char* get_status(Status status) {
    switch(status) {
        case R: return "ready";
        case E: return "finish";
        case W: return "working";
    }
}

void print(PCB* p) {
    while(p) {
        // time_t tmp = p->waiting == LONG_MAX ? 0 : cpu_time - p->waiting + 1;
        // printf("name:%-*scputime:%-4ldneedtime:%-4ld\tpriority:%-4d\tstatus:%-*s\n", 4, p->name, tmp, p->need_time, p->priority, 4, get_status(p->status));
        printf("name:%-*sneedtime:%-4ld\tpriority:%-4d\tstatus:%-*s\n", 4,
               p->name, p->need_time, p->priority, 4, get_status(p->status));
        p = p->next;
    }
    // puts("");
}

// void print3(PCB *p) {
// while(p) {
// time_t tmp = p->waiting == LONG_MAX ? 0 : cpu_time - p->waiting + 1;
// printf("name:%-*scputime:%-4ldneedtime:%-4ld\tpriority:%-4d\tstatus:%-*s\n", 4, p->name, p->waiting, p->need_time, p->priority, 4, get_status(p->status));
// p = p->next;
// }
//
// }
//
// void print2(PCB* p) {
// printf("name\troundtime\twaitingtime\n");
// while(p) {
// printf("name:%s\troundtime:%ld\twaitingtime:%ld\n", p->name, p->round, p->round - p->run_time);
// p = p->next;
// }
// }

void copy_PCB(PCB** dest, PCB** src) {
    strcpy((*dest)->name, (*src)->name);
    (*dest)->need_time = (*src)->need_time;
    (*dest)->priority = (*src)->priority;
    // (*dest)->round = (*src)->round;
    // (*dest)->waiting = (*src)->waiting;
}

void priority_scheduling_algorithm(PCB* head) {

    PCB* p = head;
    print(p);
    puts("");
    while(p && p->status == R) {
        cpu_time++;
        p->priority--;
        p->need_time--;
        // p->run_time++;
        // if(p->waiting == LONG_MAX) p->waiting = cpu_time;
        p->status = p->need_time == 0 ? E : W;
        printf("cputime:%ld\n", cpu_time);
        print(p);
        print(f_begin->next);
        puts("");
        if(p->status == W) {
            p->status = R;
            if(p->next && p->priority <= p->next->priority) {
                PCB* tmp;
                init(&tmp);
                copy_PCB(&tmp, &p);
                p = p->next;
                push(&p, tmp);
            } else
                continue;
        } else {
            // p->round = cpu_time;
            // p->waiting = cpu_time - p->run_time;
            f_end->next = p;

            f_end = p;
            p = p->next;
            f_end->next = NULL;
        }
    }
}

void input() {

    char name[10];
    time_t need_time;
    int32_t priority;
    init(&begin);
    init(&end);
    begin->priority = 127;
    end->next = begin;
    for(size_t i = 0; i < 5; i++) {
        scanf("%s%ld%d", name, &need_time, &priority);
        PCB* p;
        init(&p);
        strcpy(p->name, name);
        p->need_time = need_time;
        p->priority = priority;
        push(&begin, p);
    }
}

int main(int argc, char* argv[]) {
    freopen("/home/sirius/CODE_C/input.txt", "r", stdin);
    freopen("/home/sirius/CODE_C/output.txt", "w", stdout);
    init(&f_begin);
    f_end = f_begin;
    input();
    printf("name\t needtime \t\tpriority \t\tstatus\n");
    priority_scheduling_algorithm(begin->next);
    // int x;
    // print2(f_begin->next);

    return 0;
}
