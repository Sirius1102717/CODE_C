/*
 * @Author: Freaver
 * @Date: 2020-11-19 16:25:35
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-31 11:54:52
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student {
    int no;
    char name[20];
    int selected;
    int lab;
    int course;
    float total;
    char rank;
}STD;

typedef struct node
{
    STD data;
    struct node* next;
}NODE;
NODE* create(float* maxNo, float* as, float* al, float* ac)
{
    NODE* p;
    p = (NODE*)malloc(sizeof(NODE));
    if (p)
    {
        printf("please input your name:");
            scanf("%s", p->data.name);
        printf("please input your selected score:");
            scanf("%d", &p->data.selected);
        *as += p->data.selected;
        printf("please input your lab score");
        scanf("%d", &p->data.lab);
        *al += p->data.lab;
        printf("please input your course score");
            scanf("%d", &p->data.course);
        *ac += p->data.course;
            p->data.no = *maxNo;
        (*maxNo)++;
        p->data.total = p->data.course + p->data.lab + p->data.course;
        p->next = NULL;
    }
    return p;
}
NODE* tailinsert(NODE* tail, NODE* newNode)
{
    tail->next = newNode;
    return newNode;
}
NODE* headinsert(NODE* head, NODE* newNode)
{
    head->next = newNode;
    return head;
}
NODE* courseinsert(NODE* head, NODE* newNode)
{
    NODE* p, temp;
    p = head;
    if (newNode->data.course >= head->data.course)
        headinsert(p, newNode);
    else
    {
        while (p->next)
        {
            if (newNode->data.course <= head->data.course && newNode->data.course >= head->data.course)
            {
                temp = newNode;
                newNode = head->next->next;
                head->next = temp;
                head->next->next = newNode;
            }
            p = p->next;
        }
    }
    return p;
}