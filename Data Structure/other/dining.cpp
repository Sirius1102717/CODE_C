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
	int Table_ID;					//记录餐桌号
	int Dish_ID[N];				//记录菜的编号
	struct Order *next;
}ORDER;

typedef struct Table{
	int Table_ID;					//餐桌编号
	int  Capacity;				//餐桌最多能容纳的人数
	int Table_State;			//1 有人在用,0 没人用
}TABLE;

typedef struct Dish{
	int Dish_ID;					//菜的编号
	char Dish_Name[15];		//菜名
	float Dish_Price;			//价格
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
	printf("*********欢迎选购本店菜**********\n");
	printf("菜编号\t菜名\t菜单价\n");
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
	printf("请输入来客数量:\n");
	scanf("%d",&Cust_Num);
	if(MaxCapacity<Cust_Num){
		printf("抱歉,本店没有容纳%d的餐桌!",Cust_Num);
		return -1;
	}
	else{
		for(i=0;i<H;i++){
			 if(tb[i].Table_State==0){
				 if(tb[i].Capacity==Cust_Num)
					 return (tb[i].Table_ID);
			 }
		}
		printf("抱歉,现在没有%d人桌",Cust_Num);
	}
	printf("餐桌已满，请客人稍等一会。");
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
			printf("请输入菜的编号,按0结束输入:");
			scanf("%d",&ID);
			if(ID<0||ID>10)	{
				printf("超出菜谱范围,请重新输入\n");
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
			printf("订单创建成功\n");
		}
		else
			printf("订单创建失败\n");
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
	if((fp=fopen("历史记录.txt","a"))==NULL){
		printf("操作失败\n");
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
	printf("历史记录保存成功\n");
	fclose(fp);
}

void saveInList(float pay){
	FILE*fp;
	time_t timer;
	timer=time(NULL);
	if((fp=fopen("账目.txt","a"))==NULL){
		printf("操作失败\n");
		exit(1);
	}
	fprintf(fp,"%f\t%s\n",pay,ctime(&timer));//有问题系统时间
	printf("账本保存成功\n");
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
	printf("请输入您的餐桌号\n");
	fflush(stdin);
	scanf("%d",&ID);
	while(p!=NULL){
		if(p->Table_ID==ID){
			printf("您点菜的情况如下:\n");
			printf("编号\t菜名\t价格\n");
			while(p->Dish_ID[i]!=0){
				Display(p->Dish_ID[i]);
				pay += dish[p->Dish_ID[i]-1].Dish_Price;
				i++;
				count++;
			}
			printf("您一共点了%d道菜\n",count);
			printf("您本次的消费额为%f元\n",pay);
			printf("您实际的付款:\n");
			while(1){
				scanf("%f",&Pay);
				if(Pay >= pay)
				{
					printf("您应得的找零为%f元\n",Pay - pay);
			        printf("谢谢您的惠顾,欢迎下次光临\n");
					break;
				}
				else
				printf("您的钱不够呢，记得加钱哟\n");
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
		printf("\n此餐桌未点菜!\n");
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
	    printf("请输入初始密码：");
		scanf("%d",&PASSWORD);
	}
	
	do{
		printf("请输入密码\n");
		scanf("%d",&password);
		if(PASSWORD==password){
			printf("**********************************\n");
			printf("     欢迎进入账目管理系统\n");
			printf("**********************************\n");
			return 1;
		}
		else{
			printf("密码输入有误,请重新输入\n");
			printf("是否重新输入\n");
			printf("若重新输入请输入y\n");
			fflush(stdin);
		}
	}while(getchar()=='y');
	return 0;
}

void ModifyPW(){
	int password;
	printf("请输入新的密码\n");
	scanf("%d",&password);
	PASSWORD=password;
	printf("密码修改成功\n");
}

void List_Management(){
	FILE *fp;
	if((fp=fopen("账目.txt","r"))==NULL){
		printf("操作失败\n");
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
	if((fp=fopen("账目.txt","r"))==NULL){
		printf("操作失败\n");
		exit(1);
	}
	printf("消费金额\t消费时间\n");
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
	printf("1.修改密码\n");
	printf("2.查看账目\n");
	printf("3.返回\n");
	do{
		printf("请选择:\n");
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
      printf("没有该功能项\n");
		}
	}while(1);
}

void Main_Menu(){
	printf("\n*********************\n");
	printf("餐厅服务系统\n");
	printf("*********************\n");
	printf("1.点菜\n");
	printf("2.客户结账\n");
	printf("3.账目管理\n");
	printf("4.餐厅统计\n");
	printf("5.退出系统\n");
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
    printf("请选择:\n");
    fflush(stdin);
    scanf("%d",&choose);
    switch(choose){
      case 1:
        result=search();
        if(result==1)
          printf("您可以到%d号餐桌就餐\n",result);
        else if(result!=-1)
          printf("您和您的朋友可以到%d号餐桌就餐\n",result);
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
	fp=fopen("历史记录.txt","r");
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
	printf("菜的受欢迎程度如下：\n");
  for(i=0;i<10;i++){
    printf("\n%d菜：",i+1);
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
	printf("\n比较受顾客欢迎的四个菜是：\n");
	for(i=0;i<4;i++){
		printf("%s\n",dish[i].Dish_Name);
	}
}
int main(){
    Table_Init();
    Menu_select();
    return 0;
}
