/*
 * @Author: Freaver
 * @Date: 2021-01-18 09:22:09
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-18 10:02:12
 */

#include<stdio.h>
 // #include<stdlib.h>
 // #include<new>


typedef struct test
{
    int data;
    struct test *pre;
    struct test *next;
}TEST;

void insert(TEST **tail, TEST *node)
{
    (*tail)->next = node;
    node->pre = *tail;
    *tail = node;
}

void create(TEST **head, TEST **tail)
{
    *head = new TEST;
    *tail = *head;
    TEST *node;
    int data;
    while ( scanf("%d", &data) != EOF ) {
        node = new TEST;
        node->data = data;
        node->pre = nullptr;
        node->next = nullptr;
        insert(tail, node);
    }
    (*head)->next->pre = nullptr;

}

void headTraversal(TEST *head)
{
    TEST *p = head->next;
    while ( p ) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void tailTraversal(TEST *tail)
{
    TEST *p = tail;
    while ( p ) {
        printf("%d ", p->data);
        p = p->pre;
    }
    printf("\n");
}

TEST *headSearch(TEST *head, int data)
{
    TEST *p = head->next;
    while ( p && p->data != data ) {
        p = p->next;
    }
    return p;
}

TEST *tailSearch(TEST *tail, int data)
{
    TEST *p = tail;
    while ( p && p->data != data ) {
        p = p->pre;
    }
    return p;
}

void del(TEST *p)
{
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete(p);
}

int main(int argc, char const *argv[])
{
    TEST *head = nullptr;
    TEST *tail = nullptr;
    create(&head, &tail);
    headTraversal(head);
    int data = 3;
    // TEST *p = headSearch(head, data);
    TEST *p = tailSearch(tail, data);
    del(p);
    tailTraversal(tail);
    return 0;
}


