#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int data;
    struct queue *next;
} QUEUE;

QUEUE *rear;

void enQueue(QUEUE **rear, QUEUE *node) {
    (*rear)->next = node;
    *rear = node;
}

QUEUE *create(QUEUE *front) {
    int data;
    front = (QUEUE *) malloc(sizeof(QUEUE));
    rear = front;
    // front->next = NULL;
    QUEUE *node;
    while (scanf("%d", &data) != EOF) {
        node = (QUEUE *) malloc(sizeof(QUEUE));
        node->data = data;
        node->next = NULL;
        enQueue(&rear, node);
    }

    return front;
}

void deQueue(QUEUE *front) {
    QUEUE *p = front->next;
    front->next = p->next;
    free(p);
}

void traverse(QUEUE *front) {
    QUEUE *p = front->next;
    while (p) {
        printf("%d\n", p->data);
        p = p->next;
    }
}

int main(int argc, char const *argv[]) {
    QUEUE *front = create(front);
    deQueue(front);
    traverse(front);
    return 0;
}
