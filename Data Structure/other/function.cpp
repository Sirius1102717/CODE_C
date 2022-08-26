#include<string.h> 
#include<stdlib.h>
#include<stdio.h>
typedef struct student
{
   int num;
   int score;
   struct student *next;
}list;
list *create(int len)
{
   list *head = NULL, *node = NULL, *end = NULL;
   head = (list *)malloc(sizeof(list));
   if( !head ) {
      printf("error");
      exit(-1);
   }
   head->next = NULL;
   int i;
   for( i = 0; i < len; i++ ) {
      node = (list *)malloc(sizeof(list));
      if( !node ) {
         printf("error");
         exit(-1);
      }
      scanf("%d%d", &node->num, &node->score);
      node->next = NULL;
      if( !head->next )
         head->next = node;
      else
         end->next = node;
      end = node;
   }
   return head;
}
int isempty(list *l)
{
   return l->next == NULL;
}
int islast(list *p)
{
   return p->next == NULL;
}
list *find(int x, list *l)
{
   list *p;
   p = l->next;
   while( !p && p->next->num != x ) {
      p = p->next;
   }
   return p;
}
list *findprevious(int x, list *l)
{
   list *p;
   p = l;
   while( p->next != NULL && p->next->num != x )
      p = p->next;
   return p;
}
list *position(int n, list *l)
{
   int i;
   for( i = 1; i < n; i++ ) {
      l = l->next;   
}
   return l;
}
void delete(int n, list *l)
{
   list *p, *node;
   p = position(n, l);
   if( !islast(p) ) {
      node = p->next;
      p->next = node->next;
      free(node);
   }
}
void insert(int x, list *p)
{
   list *node;
   node = (list *)malloc(sizeof(list));
   if( node == NULL )
      printf("out of space");
   node->num = x;
   node->next = p->next;
   p->next = node;
}
void deletelsit(list *l)
{
   list *p, *node;
   p = l->next;
   l->next = NULL;
   while( !p ) {
      node = p->next;
      free(p);
      p = node;
   }
}
void traverse(int len, list *head)
{
   int i;
   for( i = 0; i < len; i++ ) {
      printf("%d %d\n", head->next->num, head->next->score);
      head = head->next;
   }
}
list *merge(list *l, list *p)
{
   list *c;
   //c=l;
   for( c = l; c->next != NULL; c = c->next );
   //c = c->next;
   c->next = p->next;
   return l;
}
/*list *order(list *l,int len)
{
    list *p,*q;
    int temp1,temp2,i;
    for(p = l,i = 1;i < len;i++,p = p->next)
    {
       for(q = p->next;q != NULL;q = q->next)
       {
          if(q->num < p->num)
          {
               temp1 = p->score;
               p->score = q->score;
               q->score = temp1;
               temp2 = p->num;
               p->num = q->num;
               q->num = temp2;
          }
       }
    }
    return l;
}*/
list *InsertSort(list *head)
{
   list *first; /*为原链表剩下用于直接插入排序的节点头指针*/
   list *t; /*临时指针变量：插入节点*/
   list *p; /*临时指针变量*/
   list *q; /*临时指针变量*/

   head = head->next;
   first = head->next; /*原链表剩下用于直接插入排序的节点链表：可根据图12来理解。*/
   head->next = NULL; /*只含有一个节点的链表的有序链表：可根据图11来理解。*/

   while( first != NULL ) /*遍历剩下无序的链表*/
   {
      /*注意：这里for语句就是体现直接插入排序思想的地方*/
      for( t = first, q = head; ((q != NULL) && (q->num < t->num)); p = q, q = q->next ); /*无序节点在有序链表中找插入的位置*/

  /*退出for循环，就是找到了插入的位置*/
  /*注意：按道理来说，这句话可以放到下面注释了的那个位置也应该对的，但是就是不能。原因：你若理解了上面的第3条，就知道了。*/
      first = first->next; /*无序链表中的节点离开，以便它插入到有序链表中。*/

      if( q == head ) /*插在第一个节点之前*/
      {
         head = t;
      }         else /*p是q的前驱*/
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
   int lena, lenb;
   while( scanf("%d%d", &lena, &lenb) != EOF )    {      
list *a, *b, *c;
      a = create(lena);
      b = create(lenb);
      c = merge(a, b);
      int lenc = lena + lenb;
      //c = InsertSort(c);
      //c = order(c,lenc);
   //a = InsertSort(a);
      traverse(lenc, c);
   }
}