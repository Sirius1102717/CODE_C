#include<stdio.h>
#include<stdlib.h>
typedef struct student{
    int num;
    int score;
}list;

typedef struct node
{
    list data;
    struct node *next;
}NODE;
NODE *merge(NODE *l,NODE *p){
   NODE *c;
   //c=l;
   for(c = l;c->next != NULL;c = c->next);
   //c = c->next;
   c->next = p->next;
   return l;}
NODE *tailinsert(NODE *tail,NODE *newNode)
{
    tail->next = newNode;
    return newNode;
}
NODE *headinsert(NODE *head,NODE *newNode)
{
    head->next = newNode;
    return head;
}
NODE *numinsert(NODE *head,NODE *newNode)
{
    NODE *p,*temp;
    p = head;
    if(newNode->data.num <= head->data.num)
    headinsert(p,newNode);
    else
    {
        while(p->next)
       {
           if(newNode->data.num >= head->data.num&&newNode->data.num <= head->next->data.num)
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
NODE *create(int len)
{
    NODE *p;
    int i;
    p = (NODE*)malloc(sizeof(NODE));
    if(p)
    {
       for(i=0;i<len;i++)
       {
           scanf("%d%d",&p->data.num,&p->data.score);
           p = p->next;
       }
    }
    p->next = NULL;
    return p;
}
/*
==========================
 功能：直接插入排序(由小到大)
 返回：指向链表表 头的指针
==========================
*/
/*
 直接插入排序的基本思想就是假设链表的前面n-1个节点是已经按键值
 （就是用它排序的字段，我们取学号num为键值）排好序的，对于节点n在
 这个序列中找插入位置，使得n插入后新序列仍然有序。按照这种思想，依次
 对链表从头到尾执行一遍，就可以使无序链表变为有序链表。
 
单向链表的直接插入排序图示：
---->[1]---->[3]----> [2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next
---->[1]---->[NULL]（从原链表中取第1个节点作为只有一个节点的有序链表）
head
图11
---->[3]---->[2]...---->[n]---->[NULL]（原链表剩下用于直接插入排序的节点）
first   3->next  2->next   n->next
图12
---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
head   1->next  2->next  3->next   n->next
图13：有N个节点的链表直接插入排序
1、先在原链表中以第一个节点为一个有序链表，其余节点为待定节点。
2、从图12链表中取节点，到图11链表中定位插入。
3、上面图示虽说画了两条链表，其实只有一条链表。在排序中，实质只增加了一个用于指向剩下需要排序节点的头指针first罢了。
   这一点请读者务必搞清楚，要不然就可能认为它和上面的选择排序法一样了。
*/
NODE *InsertSort(NODE *head)
{
    NODE *first; /*为原链表剩下用于直接插入排序的节点头指针*/
    NODE *t; /*临时指针变量：插入节点*/
    NODE *p; /*临时指针变量*/
    NODE *q; /*临时指针变量*/
 
    first = head->next; /*原链表剩下用于直接插入排序的节点链表：可根据图12来理解。*/
    head->next = NULL; /*只含有一个节点的链表的有序链表：可根据图11来理解。*/
 
    while (first != NULL) /*遍历剩下无序的链表*/
    {
        /*注意：这里for语句就是体现直接插入排序思想的地方*/
        for (t = first, q = head; ((q != NULL) && (q->data.num < t->data.num)); p = q, q = q->next); /*无序节点在有序链表中找插入的位置*/
    
    /*退出for循环，就是找到了插入的位置*/
    /*注意：按道理来说，这句话可以放到下面注释了的那个位置也应该对的，但是就是不能。原因：你若理解了上面的第3条，就知道了。*/
        first = first->next; /*无序链表中的节点离开，以便它插入到有序链表中。*/ 
  
        if (q == head) /*插在第一个节点之前*/
        {
            head = t;
        }
        else /*p是q的前驱*/
        {
            p->next = t;
        }
        t->next = q; /*完成插入动作*/
        /*first = first->next;*/
    }
    return head;
}
int main(void)
{
    int lena,lenb,lenc,i;
    scanf("%d%d",&lena,&lenb);
    NODE *c,*a,*b;
    a = create(lena);
    b = create(lenb);
    lenc = lena+lenb;
    c = merge(a,b);
    c= InsertSort(c);
    for(i = 0;i < lenc;i++)    
    {
        printf("%d %d\n",c->data.num,c->data.score);
        c = c->next;
    }
}