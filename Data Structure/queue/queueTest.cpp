/*
 * @Author: Freaver
 * @Date: 2021-01-23 23:01:38
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-31 12:02:50
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int data;
    struct queue *next;
} QUEUE;

QUEUE *rear;

void enQueue(QUEUE *&rear, QUEUE *node)
{
    rear->next = node;
    rear = node;
}

void create(QUEUE *&front)
{
    int data;
    front = (QUEUE *)malloc(sizeof(QUEUE));
    rear = front;
    // front->next = NULL;
    QUEUE *node;
    for ( int i = 0; i < 5; i++ ) {

    }
    while ( scanf("%d", &data) != EOF ) {
        node = new QUEUE;
        node->data = data;
        node->next = NULL;
        enQueue(rear, node);
    }

}

void deQueue(QUEUE *front)
{
    QUEUE *p = front->next;
    front->next = p->next;
    delete(p);
}

void traverse(QUEUE *front)
{
    QUEUE *p = front->next;
    while ( p ) {
        printf("%d\n", p->data);
        p = p->next;
    }
}

int main(int argc, char const *argv[])
{
    QUEUE *front;
    create(front);
    deQueue(front);
    traverse(front);
    return 0;
}
