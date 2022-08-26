#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int HouseNumber = 1;

typedef struct house{
    int number;
    char name[20];
    float area;
    int purchase; // 1:be purchased 2: has not been purchased
    int live; // 1:living 0:no living 2:idle
    struct house *next;
}HOUSE;
HOUSE *houseTail = NULL;

void houseInsert(HOUSE **houseTail,HOUSE *newNode){
	(*houseTail)->next = newNode;
	*houseTail = newNode;
}

HOUSE *houseLoad(HOUSE*houseHead){
	FILE *fp = fopen("house.txt","r");
	HOUSE*node = NULL;
	int number,purchase,live;
    float area;
	char name[20] = {0};
	houseHead = (HOUSE *)malloc(sizeof(HOUSE));
	houseTail = houseHead;
	while (fscanf(fp,"%d%s%f%d%d",&number,name,&area,&purchase,&live) != EOF){
		node = (HOUSE *)malloc(sizeof(HOUSE));
		node->area = area;
		strcpy(node->name,name);
        node->number = number;
        node->purchase = purchase;
        node->live = live;
		printf("%d %s %f %d %d\n",node->number,node->name,node->area,node->purchase,node->live);
		node->next = NULL;
        houseInsert(&houseTail,node);
		memset(name,0,sizeof(char) * 20);
		HouseNumber++;
	}
	node = houseHead->next;
	fclose(fp);
	return houseHead;
}

HOUSE *houseCreate(HOUSE *houseHead){
	HOUSE *node;
	char name[20] = {0};
	FILE *fp = fopen("user.txt","a+");
	houseHead = (HOUSE *)malloc(sizeof(HOUSE));
	houseTail = houseHead;
	printf("Press EOF to end input\n");
	printf("Please input the name:");
	while(scanf("%s",name) != EOF){
	    node = (HOUSE *)malloc(sizeof(HOUSE));
	    strcpy(node->name,name);
        printf("Please input the area:");
        scanf("%f",&node->area);
        printf("Please input the purchase condition\n1:purchased\n2:not purchased\n");
        scanf("%d",&node->purchase);
        while (1){
            if(node->purchase == 1 || node->purchase == 2)
                break;
            else{
                printf("Your input is error,Please input again:");
                scanf("%d",&node->purchase);
            }   
        }
        printf("Please input the live condition\n1:living\n2:no living\n3:idle");
        scanf("%d",&node->live);
        while (1){
            if(node->live == 1 || node->live == 2 || node->live == 3) 
                break;
            else{
                printf("Your input is error,Please input again:");
                scanf("%d",&node->live);
            }   
        }
        node->number = HouseNumber;
        HouseNumber++;
	    printf("%d %s %f %d %d\n",node->number,node->name,node->area,node->purchase,node->live);
	    fprintf(fp,"%-10d%-10s%-10f%-10d%-10d\n",node->number,node->name,node->area,node->purchase,node->live);
        node->next = NULL;
	    houseInsert(&houseTail,node);
	    memset(name,0,sizeof(char) * 20);
	    printf("Press the EOF to end input\n");
	    printf("please input the name:");
	}
	if(HouseNumber == 1)
		node = houseHead->next;
	fclose(fp);
	return houseHead;
}

HOUSE *houseNumSearch(HOUSE *houseHead,int number){
	HOUSE *p;
	p = houseHead;
	while(p->next && p->next->number != number){
        p = p->next;
	}
	if(p->next->number == number)
		return p;
	else
		perror("error search\n");
}

HOUSE *houseNameSearch(HOUSE *houseHead,char name[]){
	HOUSE *p = houseHead;
	while(p->next && strcmp(p->next->name,name) != 0) {
		p = p->next;
	}
	if(strcmp(p->next->name,name) == 0)
		return p;
	else
		perror("error search\n");
}

void houseSearch(HOUSE *houseHead){
	printf("Please choose the way:\n1.name\n2.number\n");
	int choose;
	char name[20] = {0};
	int number;
	HOUSE *prePosition,*curPosition;
	scanf("%d",&choose);
	if(choose == 1){
		printf("Please input the name:");
		scanf("%s",name);
		prePosition = houseNameSearch(houseHead, name);
		curPosition = prePosition->next;
	}
	else{
		printf("Please input the number:");
		scanf("%d",&number);
		prePosition = houseNumSearch(houseHead, number);
		curPosition = prePosition->next;
	}
	printf("%d %s %f %d %d\n",curPosition->number,curPosition->name,curPosition->area,curPosition->number,curPosition->live);
}

void houseNodeDelete(HOUSE *pre){
	HOUSE *cur = pre->next;
	pre->next = cur->next;
	free(cur);
}

void houseNameFileDel(FILE *fp,FILE *rp,HOUSE *pre){
	HOUSE *chan, *cur = pre->next;
	chan = (HOUSE *)malloc(sizeof(HOUSE));
	while(fscanf(fp,"%d%s%f%d%d",&chan->number,chan->name,&chan->area,&chan->purchase,&chan->live) != EOF){
		if(strcmp(cur->name,chan->name) == 0)
			continue;
		else
			fprintf(rp,"%-10d%-10s%-10f%-10d%-10d\n",chan->number,chan->name,chan->area,chan->purchase,chan->live);
    }
}

void houseNumFileDel(FILE *fp,FILE *rp,HOUSE *pre){
	HOUSE *chan, *cur = pre->next;
	chan = (HOUSE *)malloc(sizeof(HOUSE));
	while(fscanf(fp,"%d%s%f%d%d",&chan->number,chan->name,&chan->area,&chan->purchase,&chan->live) != EOF){
		if(cur->number == chan->number)
			continue;
		else
			fprintf(rp,"%-10d%-10s%-10f%-10d%-10d\n",chan->number,chan->name,chan->area,chan->purchase,chan->live);
	}
}

void houseFileDelete(HOUSE *houseHead,char name[],int number,int choose){
	FILE *fp = fopen("house.txt","r");
	FILE *rp = fopen("temp.txt","w");
	HOUSE *position;
	int err;
	switch(choose){
		case 1:
			position = houseNameSearch(houseHead,name);
			houseNameFileDel(fp,rp,position);
			break;
		default:
			position = houseNumSearch(houseHead,number);
			houseNumFileDel(fp,rp,position);
    }
	houseNodeDelete(position);
	fclose(fp);
	fclose(rp);
	err = remove("house.txt");
	if(err == 0)
		printf("Delete successfully\n");
	else
		perror("error delete\n");
    rename("temp.txt","house.txt");
}

void houseDelete(HOUSE *houseHead){
    int choose;
    char name[20];
    int number;
    printf("Please choose the way:\n1.name\n2.number\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            printf("Please input the name to delete:");
            scanf("%s",name);
            break;
        default:
            printf("Please input the number to delete:");
            scanf("%d",&number);
    }
    houseFileDelete(houseHead,name,number,choose);
    printf("The delete had been finished\n");
}

void houseNumModify(int number, HOUSE **houseHead){
    HOUSE *position = houseNumSearch(*houseHead,number)->next;
    HOUSE chan;
    FILE *fp = fopen("user.txt","r+");
    int newNum;  
    printf("Please input the new number:");
    scanf("%d",&newNum);
    while(fscanf(fp,"%d%s%f%d%d",&chan.number,chan.name,&chan.area,&chan.purchase,&chan.live) != EOF){
        if(position->number == chan.number){
            fseek(fp,-41,SEEK_CUR);
            fprintf(fp,"%d",newNum);
            break;
        }
    }
    position->number = newNum;
    printf("%d %s %f %d %d",position->number,position->name,position->area,position->purchase,position->live);
    fclose(fp);
}

void houseNameModify(char name[], HOUSE **houseHead){
    HOUSE *position = houseNameSearch(*houseHead,name)->next;
    HOUSE chan;
    FILE *fp = fopen("user.txt","r+");
    char newName[20] = {0};
    printf("Please input the new name:");
    scanf("%s",newName);
    while(fscanf(fp,"%d%s%f%d%d",&chan.number,chan.name,&chan.area,&chan.purchase,&chan.live) != EOF){
        if(strcmp(position->name,chan.name) == 0){
            fseek(fp,-31,SEEK_CUR);
            fprintf(fp,"%s",newName);
            break;
        }
    }
    strcpy(position->name,newName);
    printf("%d %s %f %d %d",position->number,position->name,position->area,position->purchase,position->live);
    fclose(fp);
}

HOUSE *houseModify(HOUSE *houseHead){
    int choose;
    char name[20] = {0};
    int number;
    printf("Please choose the way:\n1.number\n2.name\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            printf("Please input the number:"); 
            scanf("%d",&number);
            houseNumModify(number,&houseHead);
            break;
        default:
            printf("Please input the name:");
            scanf("%s",name);
            houseNameModify(name,&houseHead);
    }
    return houseHead;
}

HOUSE *houseManage(HOUSE *houseHead){
    int choose;
    houseHead = houseLoad(houseHead);
    printf("Please input your choice:\n1:Create\n2:Delete\n3.Search\n4.Modify\n");
    scanf("%d",&choose);
    switch(choose){
        case 1: 
            houseHead = houseCreate(houseHead);
            break;
        case 2: 
            houseDelete(houseHead);
            break;
        case 3:
            houseSearch(houseHead);
            break;
        default: 
            houseHead = houseModify(houseHead);
    }
    return houseHead;
}

int main(int argc, char const *argv[]){
    HOUSE *houseHead;
    houseHead = houseManage(houseHead);
    return 0;
}


