#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int MemberNumber = 1;

typedef struct member {
    int num;
    char name[20];
    int age;
    struct member *next;
}MEMBER;
MEMBER *memTail = NULL;

MEMBER *memLoad(MEMBER *head){
    FILE *fp = fopen("member.txt","r");
    MEMBER *node = NULL;
    int num,age;
    char name[20] = {0};
    head->next = NULL;
    head = (MEMBER *)malloc(sizeof(MEMBER));
    while(fscanf(fp,"%d\t%s\t%d",&num,name,&age) != EOF){
        node = (MEMBER *)malloc(sizeof(MEMBER));
        node->num = num;
        node->age = age;
        strcpy(node->name,name);
        printf("%d %s %d",node->num,node->name,node->age);
        node->next = NULL;
        memTail->next = node;
        memTail = node;
        memset(name,0,sizeof(char));
    }
    node = head->next;
    fclose(fp);
    return head;
}

MEMBER *memCreate(MEMBER *memHead){
    MEMBER *node;
    char name[20] = {0};
    FILE *fp = fopen("member.txt","r+");
    memHead = (MEMBER *)malloc(sizeof(MEMBER));
    memTail = memHead;
    printf("Press EOF to end input\n");
    printf("Please input the name:");
    while(scanf("%s",name) != EOF){
        node = (MEMBER *)malloc(sizeof(MEMBER));
        strcpy(node->name,name);
        printf("Please input the age:");
        scanf("%d",&node->age);
        node->num = MemberNumber;
        printf("%d %s %d\n",node->num,node->name,node->age);
        fprintf(fp,"%d\t%s\t%d\n",node->num,node->name,node->age);
        MemberNumber++;
        node->next = NULL;
        memTail->next = node;
        memTail = node;
        memset(name,0,sizeof(char));
        printf("Press EOF to end input\n");
        printf("Please input the name:");
    }
    node = memHead->next;
    fclose(fp);
    return memHead;
}

MEMBER *memNameSearch(char name[], MEMBER *head){
    MEMBER *p;
    p = head->next;
    while(p && strcmp(name,p->name) != 0){
    if(strcmp(name,p->name) == 0)
        printf("%d %s %d",p->num,p->name,p->age);
        p = p->next;
    }
    if(strcmp(name,p->name) == 0)
        return p;
    else
        printf("error search\n");
}

MEMBER *memNumSearch(int num, MEMBER *head){
    MEMBER *p;
    p = head->next;
    while(p && p->num != num){
            p = p->next;
    }
    if(p->num == num)
        return p;
    else
        printf("error search\n");
}

MEMBER *memberManage(MEMBER *head)
{
    int choose;
    memLoad(head);
    system("cls");
    printf("Please input your choice:\n");
    printf("1:Create\n2:Delete\n3.Search\n4.Modify\nPlease input your choice:");
    scanf("%d",&choose);
    switch(choose){
        case 1:head = memCreate(head);
            break;
       // case 2:memDelete(head);
            //break;
        case 3:memSearch(head);
            break;
        //default:memModify(head);
    }
    return head;
}
void memSearch(MEMBER *head){
    printf("Please choose the way:\n1.name\n2.number\n");
    int choose;
    char name[20] = {0};
    int num;
    MEMBER *position;
    scanf("%d",&choose);
    if(choose == 1){
        printf("Please input the name:");
        scanf("%s",name);
        position = memNameSearch(name, head);
    }
    else{
        printf("Please input the number:");
        scanf("%d",&num);
        position = memNumSearch(num, head);
    }
    printf("%d %s %d",position->num,position->name,position->age);


}

int main(){
    MEMBER *head = NULL;
    head = memberManage(head);
    memSearch(head);
    //printf("%d %s %d",p->num,p->name,p->score);
    return 0;
}