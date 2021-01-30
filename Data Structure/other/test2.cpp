/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
    int num;
    int score;
    struct student *next;
};
typedef struct student list;
int test(list *l)
{
    return l->next==NULL;
}
void create(list *l)
{
    list *node,*head,*end;
    node=(list)malloc(sizeof(list));
    node=node->next;
    head=head->next;
    end->next=NULL;
    scanf("%d%d",&node->num,&node->score);
}
void print(list *l)
{
    printf("%d %d",head->num,head->score);
}
int main(void)
{
    list *a,*b;
    create(list *a);
    print(list *a);
}*/
#include<stdio.h>
#include<string.h>
int main(void)
{
    char a[90]={0};
    int i,j,n,m=0,counter=0,b1=0;
    char p[20][20]={0};
    char b[90]={0};
    gets(a);
    n=strlen(a);
    for(i=0;i<n;i++)
    {
        if(a[i]==' '||a[i+1]=='\0')
        {
            if(m==0)
            {
                for(j=0;j<i;j++)
                {
                    b[b1]=a[j];
                    b1++;
                }
                strcpy(p[counter],b);
                for(j=0;j<=b1;j++)
                b[j]='\0';
                b1=0;
                counter++;
                m=i;
            }
            else
            {
                for(j=m+1;j<i;j++)
                {
                    b[b1]=a[j];
                    b1++;
                }
                strcpy(p[counter],b);
                b1=0;
                for(j=0;j<=b1;j++)
                b[j]='\0';
                b1=0;
                counter++;
                m=i;
            } 
        }
    }
    for(i=0;i<counter;i++)
    printf("%s",p[counter-i-1]);
}

