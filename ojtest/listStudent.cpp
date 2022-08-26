/*
 * @Author: Freaver
 * @Date: 2020-12-26 14:19:03
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-15 19:04:06
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    int number;
    int score;
    struct student *next;
} STU;

void insert(STU **tail, STU *node) {
    (*tail)->next = node;
    *tail = node;
}

void nodeChange(STU *pre, STU *change1, STU *change2) {
    STU *temp = (change2)->next;
    // (*pre)->next = *change2;
    // (*change1)->next = (*change2)->next;
    // (*change2)->next = temp;
    // (*change1) = temp;
    (pre)->next = change2;
    (change2)->next = change1;
    (change1)->next = temp;
}

STU *change(STU *a, STU *b, STU *aTail, int length) {
    insert(&aTail, b->next);
    int i, j;
    STU *pre = a;
    for (i = 0; i < length - 1; i++) {
        for (j = 0; j < length - 1; j++) {
            if (pre->next->number > pre->next->next->number) {
                nodeChange(pre, pre->next, pre->next->next);
            }
            pre = pre->next;
        }
        pre = a;
    }
    return a;
}

void traverse(STU *a) {
    while (a->next) {
        printf("%d %d\n", a->next->number, a->next->score);
        a = a->next;
    }
    system("pause");
}

STU *create(STU *head, STU **tail, int length) {
    head = (STU *)malloc(sizeof(STU));
    *tail = head;
    STU *node;
    int i;
    for (i = 0; i < length; i++) {
        node = (STU *)malloc(sizeof(STU));
        scanf("%d%d", &node->number, &node->score);
        node->next = NULL;
        insert(tail, node);
    }
    return head;
}

int main(void) {
    int n, m;
    // scanf("%d%d", &n, &m);
    n = 2;
    m = 3;
    STU *aTail, *bTail;
    STU *a = create(a, &aTail, n);
    STU *b = create(b, &bTail, m);
    STU *as = change(a, b, aTail, m + n);
    traverse(as);
    return 0;
}
