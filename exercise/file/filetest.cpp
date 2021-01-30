#include<stdio.h>
#include<stdlib.h>

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
    head = (MEMBER *)malloc(sizeof(MEMBER));
    memTail = head;
    while(fscanf(fp,"%d%s%d",&num,name,&age) != EOF){
        node = (MEMBER *)malloc(sizeof(MEMBER));
        node->num = num;
        node->age = age;
        strcpy(node->name,name);
        printf("%d %s %d\n",node->num,node->name,node->age);
        node->next = NULL;
        memTail->next = node;
        memTail = node;
        memset(name,0,sizeof(char));
        MemberNumber++;
    }
    node = head->next;
    fclose(fp);
    return head;
}

MEMBER *memNameSearch(char name[], MEMBER *head){
    MEMBER *p;
    p = head;
    while(p->next && strcmp(name,p->next->name) != 0){
        p = p->next;
    }
    if(strcmp(name,p->next->name) == 0)
        return p;
    else
        printf("error search\n");
}

void memNameModify(char name[], MEMBER **head){
    MEMBER *position = memNameSearch(name,*head)->next;
    MEMBER chan;
    FILE *fp = fopen("member.txt","r+");
    char newName[20] = {0};
    int lenName;
    printf("Please input the newname:");
    scanf("%s",newName);
    lenName = strlen(position->name);
    while(fscanf(fp,"%d%s%d",&chan.num,chan.name,&chan.age) != EOF){
        if(strcmp(position->name,chan.name) == 0){
            fseek(fp,-(3 + lenName),SEEK_CUR);
            fprintf(fp,"%s",newName);
            break;
        }
    }
    strcpy(position->name,newName);
    printf("%d %s %d\n",position->num,position->name,position->age);
    fclose(fp);
}

int main(void){
    MEMBER *head;
    char name[20];
    head = memLoad(head);
    printf("Please input the name to modify\n");
    scanf("%s",name);
    memNameModify(name, &head);
}
