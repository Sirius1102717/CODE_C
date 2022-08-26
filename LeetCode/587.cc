/*
 * @Author: Freaver
 * @Date: 2021-01-26 22:54:36
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-27 00:39:58
 */

#include <atomic>
#include<bits/stdc++.h>
#include <cstdlib>
using namespace std;

class test
{

public:
    int x;
    int y;
    test *pre;
    test *next;
    test(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

};

void f(test *cur)
{
    test *pre = cur->pre;
    test *next = cur->next;
    float first = (pre->x - cur->x) * (pre->x - cur->x) + (pre->y - cur->y) * (pre->y - cur->y);
    float second = (next->x - cur->x) * (next->x - cur->x) + (next->y - cur->y) * (next->y - cur->y);
    float third = (pre->x - next->x) * (pre->x - next->x) + (pre->y - next->y) * (pre->y - next->y);
    if ( (first * first + second * second) >= third * third ) {
        pre->next = next;
        next->pre = pre;
        delete(cur);
    }
}

void create(test **head, test **tail, int n)
{
    int x;
    int y;
    int i;
    *head = new test(0, 0);
    *tail = *head;
    test *node;
    for ( i = 0; i < n; i++ ) {
        cin >> x >> y;
        node = new test(x, y);
        node->pre = *tail;
        node->next = nullptr;
        (*tail)->next = node;
        *tail = node;

    }
}

void traversal(test *head)
{
    test *p = head->next;
    while ( p ) {
        cout << "[" << p->x << "," << p->y << "]" << "\n";
        p = p->next;
    }
}

int main(int argc, char const *argv[])
{
    test *head, *tail;
    int n = 6;
    create(&head, &tail, n);
    f(head->next->next);
    traversal(head);
    return 0;
}
