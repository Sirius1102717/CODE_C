#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define D 10
#define H 10
#define N 15
#define MaxCapacity 50
int i;
int PASSWORD = 0;
typedef struct Order{
	int Table_ID;					//��¼������
	int Dish_ID[N];				//��¼�˵ı��
	struct Order *next;
}ORDER;

typedef struct Table{
	int Table_ID;					//�������
	int  Capacity;				//������������ɵ�����
	int Table_State;			//1 ��������,0 û����
}TABLE;

typedef struct Dish{
	int Dish_ID;					//�˵ı��
	char Dish_Name[15];		//����
	float Dish_Price;			//�۸�
}DISH;

TABLE tb[H];
DISH dish[D];

void Table_Init(){
	tb[0].Capacity=1;tb[0].Table_ID=1;
	tb[1].Capacity=1;tb[1].Table_ID=2;
	tb[2].Capacity=2;tb[2].Table_ID=3;
	tb[3].Capacity=2;tb[3].Table_ID=4;
	tb[4].Capacity=2;tb[4].Table_ID=5;
	tb[5].Capacity=3;tb[5].Table_ID=6;
	tb[6].Capacity=4;tb[6].Table_ID=7;
	tb[7].Capacity=4;tb[7].Table_ID=8;
	tb[8].Capacity=4;tb[8].Table_ID=9;
	tb[9].Capacity=4;tb[9].Table_ID=10;
}

void Load_Dish(){
	FILE *fp;
	int i;
    fp=fopen("dish_name.txt","r");
	for(i=0;i<D;i++){
		fscanf(fp,"%d\t%s\t%f",&dish[i].Dish_ID,dish[i].Dish_Name,&dish[i].Dish_Price);
	}
	fclose(fp);
}

void Dish_Menu(void){
	printf("*********��ӭѡ�������**********\n");
	printf("�˱��\t����\t�˵���\n");
	for(i=0;i<D;i++)
	   printf("%d\t%s\t%f\n",dish[i].Dish_ID,dish[i].Dish_Name,dish[i].Dish_Price);
}

void Display(int ID){
	int i=0;
	for(i=0;i<D;i++){
		if(dish[i].Dish_ID==ID){
			printf("%d\t%s\t%f\n",dish[i].Dish_ID,dish[i].Dish_Name,dish[i].Dish_Price);
			break;
		}
	}
}

int search(void){
	int Cust_Num;
	int i;
	printf("��������������:\n");
	scanf("%d",&Cust_Num);
	if(MaxCapacity<Cust_Num){
		printf("��Ǹ,����û������%d�Ĳ���!",Cust_Num);
		return -1;
	}
	else{
		for(i=0;i<H;i++){
			 if(tb[i].Table_State==0){
				 if(tb[i].Capacity==Cust_Num)
					 return (tb[i].Table_ID);
			 }
		}
		printf("��Ǹ,����û��%d����",Cust_Num);
	}
	printf("����������������Ե�һ�ᡣ");
	return -1;
}

ORDER* CreateOne(int result){
	ORDER *p;
	int i, ID;
	p = (ORDER *)malloc(sizeof(ORDER));
	for(i=0;i<D;i++)
		p->Dish_ID[i]=0;
	if(result!=-1){
		p->Table_ID=result;
		for(i=0;i<D;i++){
			printf("������˵ı��,��0��������:");
			scanf("%d",&ID);
			if(ID<0||ID>10)	{
				printf("�������׷�Χ,����������\n");
				continue;
			}
			else if(ID==0)
					break;
			else p->Dish_ID[i]=ID;
		}
		tb[result-1].Table_State=1;
	}
	p->next=NULL;
	return p;
}

ORDER* Dish_Order(ORDER *head,ORDER *p){
	ORDER *p1;
	p1=head;
	if(head!=NULL){
		if(p!=NULL){
			while(p1->next!=NULL){
				p1=p1->next;
			}
			p1->next=p;
			printf("���������ɹ�\n");
		}
		else
			printf("��������ʧ��\n");
	}
	else{
		if(p!=NULL)
			head=p;
	}
	return head;
}

void Save_Inform(ORDER *p,int m){
	FILE *fp;
	time_t timer;
	int i=0;
	timer=time(NULL);
	if((fp=fopen("��ʷ��¼.txt","a"))==NULL){
		printf("����ʧ��\n");
		exit(1);
	}
	fprintf(fp,"%d\n",m);
	while(p->Dish_ID[i]>0){
		fprintf(fp,"%d\t%s\t%f\n",dish[p->Dish_ID[i]-1].Dish_ID,
            									dish[p->Dish_ID[i]-1].Dish_Name,
            									dish[p->Dish_ID[i]-1].Dish_Price);
		i++;
	}
	fprintf(fp,"%s",ctime(&timer));
	printf("��ʷ��¼����ɹ�\n");
	fclose(fp);
}

void saveInList(float pay){
	FILE*fp;
	time_t timer;
	timer=time(NULL);
	if((fp=fopen("��Ŀ.txt","a"))==NULL){
		printf("����ʧ��\n");
		exit(1);
	}
	fprintf(fp,"%f\t%s\n",pay,ctime(&timer));//������ϵͳʱ��
	printf("�˱�����ɹ�\n");
	fclose(fp);
}

ORDER *Payment(ORDER *head){
	int i=0;
	int count=0;
	float pay=0.0;
	float Pay;
	int ID;
	ORDER *p,*p1;
	p=head;
	p1=NULL;
	printf("���������Ĳ�����\n");
	fflush(stdin);
	scanf("%d",&ID);
	while(p!=NULL){
		if(p->Table_ID==ID){
			printf("����˵��������:\n");
			printf("���\t����\t�۸�\n");
			while(p->Dish_ID[i]!=0){
				Display(p->Dish_ID[i]);
				pay += dish[p->Dish_ID[i]-1].Dish_Price;
				i++;
				count++;
			}
			printf("��һ������%d����\n",count);
			printf("�����ε����Ѷ�Ϊ%fԪ\n",pay);
			printf("��ʵ�ʵĸ���:\n");
			while(1){
				scanf("%f",&Pay);
				if(Pay >= pay)
				{
					printf("��Ӧ�õ�����Ϊ%fԪ\n",Pay - pay);
			        printf("лл���Ļݹ�,��ӭ�´ι���\n");
					break;
				}
				else
				printf("����Ǯ�����أ��ǵü�ǮӴ\n");
			}
			if(count>0){
				saveInList(pay);
				Save_Inform(p,count);
			}
			tb[p->Table_ID-1].Table_State=0;
			break;
    }
		else{
			p1=p;
			p=p->next;
		}
	}
	if(p==NULL){
		printf("\n�˲���δ���!\n");
  }else if(p==head){
    free(p);
    p=NULL;
  }else{
    p1->next=p->next;
    free(p);
    p=NULL;
  }
	getch();
	return head;
}

int Pass_Word(){
	int password = 0;
	if(PASSWORD == 0){
	    printf("�������ʼ���룺");
		scanf("%d",&PASSWORD);
	}
	
	do{
		printf("����������\n");
		scanf("%d",&password);
		if(PASSWORD==password){
			printf("**********************************\n");
			printf("     ��ӭ������Ŀ����ϵͳ\n");
			printf("**********************************\n");
			return 1;
		}
		else{
			printf("������������,����������\n");
			printf("�Ƿ���������\n");
			printf("����������������y\n");
			fflush(stdin);
		}
	}while(getchar()=='y');
	return 0;
}

void ModifyPW(){
	int password;
	printf("�������µ�����\n");
	scanf("%d",&password);
	PASSWORD=password;
	printf("�����޸ĳɹ�\n");
}

void List_Management(){
	FILE *fp;
	if((fp=fopen("��Ŀ.txt","r"))==NULL){
		printf("����ʧ��\n");
		exit(1);
	}
	if(Pass_Word())
		ListMenu();
}
void Observe(){
	FILE *fp;
	float pay;
	char str[25];
	int i=0;
	int j=0;
	if((fp=fopen("��Ŀ.txt","r"))==NULL){
		printf("����ʧ��\n");
		exit(1);
	}
	printf("���ѽ��\t����ʱ��\n");
	while(!feof(fp)){
		i=0;
		j=0;
		fscanf(fp,"%f\t",&pay);
		while(i<=5&&j<25){
			fscanf(fp,"%c",&str[j]);
			j++;
			if(str[j]==' ')
				i++;
		}
		fscanf(fp,"\n\n");
		i=0;
		j=0;
		printf("%f\t",pay);
		while(i<=5&&j<25){
			printf("%c",str[j]);
			j++;
			if(str[j]==' ')
				i++;
		}
		printf("\n");
	}
	fclose(fp);
}

void ListMenu(){
	int choice;
	printf("1.�޸�����\n");
	printf("2.�鿴��Ŀ\n");
	printf("3.����\n");
	do{
		printf("��ѡ��:\n");
		scanf("%d",&choice);
		switch(choice)	{
		case 1:
      ModifyPW();
      break;
		case 2:
      Observe();
			break;
		case 3:
      Menu_select();
			break;
		default:
      printf("û�иù�����\n");
		}
	}while(1);
}

void Main_Menu(){
	printf("\n*********************\n");
	printf("��������ϵͳ\n");
	printf("*********************\n");
	printf("1.���\n");
	printf("2.�ͻ�����\n");
	printf("3.��Ŀ����\n");
	printf("4.����ͳ��\n");
	printf("5.�˳�ϵͳ\n");
}

void Menu_select(void){
	ORDER* head;
	int choose;
	int result;
	head=NULL;
	system("cls");
	do{
    Load_Dish();
    Main_Menu();
    printf("��ѡ��:\n");
    fflush(stdin);
    scanf("%d",&choose);
    switch(choose){
      case 1:
        result=search();
        if(result==1)
          printf("�����Ե�%d�Ų����Ͳ�\n",result);
        else if(result!=-1)
          printf("�����������ѿ��Ե�%d�Ų����Ͳ�\n",result);
        else
          break;
		Dish_Menu();
        head=Dish_Order(head,CreateOne(result));
        break;
      case 2:	head=Payment(head);
        break;
      case 3:	List_Management();
        break;
      case 4:	Get_Rank();
        break;
      case 5:	exit(1);
        break;
		}
	}while(1);
}

void Get_Rank(void){
	FILE *fp;
	int n,i,m=0,j;
	int count[10]={0},t=0;
	char s[16]="",a[10];
	fp=fopen("��ʷ��¼.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d\n",&n);
		i=0;
		while(i!=n){
			fscanf(fp,"%d%*s%*s",&m,s,s);
			for(j=0;j<10;j++){
				if(m==dish[j].Dish_ID){
					count[j]++;
					break;
				}
			}
			i++;
			if(i==n)
				fscanf(fp,"%*s%*s%*s%*s%*s\n",s,s,s,s,s);
		}
	}
	printf("�˵��ܻ�ӭ�̶����£�\n");
  for(i=0;i<10;i++){
    printf("\n%d�ˣ�",i+1);
    for(j=0;j<count[i];j++)
      printf(" * ");
	}
	for(i=0;i<9;i++){
		for(j=0;j<9-i;j++){
			if(count[j]<count[j+1]){
				t=count[j];
				strcpy(a,dish[j].Dish_Name);
				count[j]=count[j+1];
				strcpy(dish[j].Dish_Name,dish[j+1].Dish_Name);
				count[j+1]=t;
				strcpy(dish[j+1].Dish_Name,a);
			}
		}
	}
	printf("\n�Ƚ��ܹ˿ͻ�ӭ���ĸ����ǣ�\n");
	for(i=0;i<4;i++){
		printf("%s\n",dish[i].Dish_Name);
	}
}
int main(){
    Table_Init();
    Menu_select();
    return 0;
}
