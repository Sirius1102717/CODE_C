#include <stdio.h>
#include <stdlib.h>

typedef struct test {
    int data;
    struct test *next;
}TEST;

TEST *tail;

void insert(TEST **tail, TEST *node) {
    (*tail)->next = node;
    *tail = node;
}

void testInsert(TEST *tail, TEST *node) {
    tail->next = node;
    tail = node;
}

void nodeChange(TEST *pre, TEST *change1, TEST *change2) {
    TEST *temp = (change2)->next;
    // (*pre)->next = *change2;
    // (*change1)->next = (*change2)->next;
    // (*change2)->next = temp;
    // (*change1) = temp;
    (pre)->next = change2;
    (change2)->next = change1;
    (change1)->next = temp;
}

TEST *create(TEST *head) {
    int a, i, j;
    int length = 4;
    head = (TEST *)malloc(sizeof(TEST));
    tail = head;
    TEST *node;
    for(a = 1 ; a < 4; a++) {
        node = (TEST *)malloc(sizeof(TEST));
        node->data = a;
        node->next = NULL;
        testInsert(tail,node);
        // insert(&tail,node);
    }
    TEST *pre = head->next;

    // for (i = 0; i < length; i++) {
        // for (j = 0; j < length ; j++) {
            // if (pre->next->data > pre->next->next->data) {
                nodeChange(pre, pre->next, pre->next->next);
            // }
            // pre = pre->next;
        // }
        // pre = head;
    // }
    return head;
}

int main(void) {
    TEST *head = create(head);
    while(head->next) {
        printf("%d ",head->next->data);
        head = head->next;
    }
    return 0;
}