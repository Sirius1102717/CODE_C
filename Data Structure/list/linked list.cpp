#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student{
        int num;
        int score;
        struct student *next;
}list;

list *listcreate(int len)
{
    list *head=NULL,*node=NULL,*end=NULL;
    head=(list*)malloc(sizeof(list));
	if(!head)
	{
		printf("error");
		exit(-1);
	}
	head->next=NULL;
    int i;
    for(i=0;i<len;i++)
    {
        node=(list*)malloc(sizeof(list));
        if(!node)
		{
			printf("error");
			exit(-1);
		}
        scanf("%d%d",&node->num,&node->score);
        node->next=NULL;
        if(!head->next)
            head->next=node;
        else
            end->next=node;
        end=node;
    }
        return head;
}
list *listsearch(int k,list *head)
{
    list *node;
    node=head;
    int i=1;
    while ((i<k)&&node)
    {
        node=node->next;
        i++;
    }
    if((i==k)&&node)
        return node;
    else
        {
            printf("error");
            return NULL;
        }
}
list *listtraverse(int len,list *head)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%d %d\n",head->next->num,head->next->score);
        head=head->next;
    }
}
list *listdelete(int len,int n,list *head)
{
    int i;
    list *node1=NULL,*node2=NULL;
    if(n>len&&n<1)
    printf("error");
    else
    {
        if(n==1)
            node1=head;
        else
        {
            node1=listsearch(n-1,head);
        }
        node2=node1->next;
        if(node1&&node2)
        {
            node1->next=node2->next;
            free(node1);
            return 1;
        }
        else
        {
            printf("error");
            return 0;
        }
    }

}
int main(void)
{
    int len = 1,n;
    scanf("%d",&n);
    list *head;
    head=listcreate(len);
    head = listsearch(n,head);
    printf("%d %d",head->num,head->score);
    //listtraverse(len,head);
}
