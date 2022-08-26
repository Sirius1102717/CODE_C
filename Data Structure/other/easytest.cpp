#include<string.h>
#include<stdio.h>
#include<conio.h>
char ch={0};//单个字符
int numarr[30];//存放最终计算的数字的数组(Number array)
int num_i=0;//(Number index)
int fn=0;//存放最终的结果(finish number)
char tnsarr[30];//存放数字字符的临时字符串数组(Temporary Number String Array)
int tnsa_i=0;//上面数组的下标(Temporary number string array index)
char jsarr[30];//存放+-字符的临时字符串数组(jia/jian string array)
int jsa_i=0;//上面数组的下标(jia/jian string array index)
int tcnarr[30];//存放乘除数字的临时整型数组(Temporary cheng/chu number array)
int tcna_i=0;//上面数组的下标(Temporary cheng/chu number array index)
char csarr[30];//存放*/字符的临时字符串数组(cheng/chu string array)
int csa_i=0;//上面数组的下标(cheng/chu string array index)
int isj=0;//是否执行过乘除操作的标志。如果是则值为1，否则为0
int tfn=0;//所有乘除的积或商

/*函数声明*/
void Count(void);//主要函数，用于获取用户输入和判断用户输入以调用其他函数执行操作
void setJstr(void);//处理用户输入的'+'和'-'
void setCstr(void);//处理用户输入的'*'和'/'
void setKstr(void);//处理用户输入的'('和')'
void setNumberstr(char ch);//处理数字
void iniTsarr(void);//初始化临时数字字符串数组
void countC();//计算所有乘除的和
void inic();//初始化乘除操作
void finish(void);//最后调用该函数，将计算结果赋给fn变量
void iniAll(void);//初始化所有变量。让程序可以重复运行

int main(void)
{
	while(1)
	{
	Count();
	if('\0'!=tnsarr[0]||'\0'!=jsarr[0])//如果发现这两个字符数组有一个为空，则认为用户什么都没有输入
	{
				printf("\n%d\n",fn);
	}

	
	//初始化所有变量

	iniAll();
	}
	return 0;
}

void Count()
{
/*计算*/

	while(1)//如果用户输入回车则停止获取
	{
		ch=getch();

		if('*'==ch||'/'==ch){
		//处理*/
		setCstr();
		}
		
		
		if('+'==ch||'-'==ch)
		//处理+-
		setJstr();
		
		
		if(ch>=48&&ch<=57)
		//处理数字
		setNumberstr(ch);
		
		if('e'==ch)//退出程序
		exit(0);
		
		//计算机结果(跳出循环获取键盘)
		if('='==ch||'\r'==ch)
		{
			
			numarr[num_i]=atoi(tnsarr);//将临时字符串中的数字转换成整型数字赋给主数组
			++num_i;
			//iniTsarr();
	//			printf("this3");
			break;
		}
		
		
	}
	
	finish();//最终计算
	//	printf("this4");
	return ;
}


//处理加减
void setJstr(){
	/*处理+-,将+-存入字符数组*/
	printf("%c",ch);
	//printf("\n执行setJstr\n");
	if(0==isj)//isj只能生效一次。一次过后又回到0的状态。因为下面的代码
	{
	numarr[num_i]=atoi(tnsarr);//将临时字符串中的数字转换成整型数字赋给主数组
	++num_i;
	}
	isj=0;
	iniTsarr();//清空临时数组
	jsarr[jsa_i]=ch;
	++jsa_i;
	
	return;
}


//处理乘除
void setCstr()
{
	printf("%c",ch);
	
	tcnarr[tcna_i]=atoi(tnsarr);//将*号前的数字赋给临时整型数组
	++tcna_i;
	iniTsarr();//初始化tnsarr数组
	csarr[csa_i]=ch;//将*或/符号赋给临时字符数组
	++csa_i;
	
	/*********************************/
	//printf("\n(%d)\n",tcnarr[tcna_i-1]);
//	printf("\n(%c)\n ",csarr[csa_i-1]);
	/*********************************/
	
	countC();
	//printf("\n跳出刚刚的函数\n");
	return;
}
void countC(){
	
	//printf("\n执行countC\n");
	while(1)
	{
		ch=getch();
		if(ch>=48&&ch<=57)
			setNumberstr(ch);
		if('*'==ch||'/'==ch)
		{
			setCstr();
			return;
		}
			
			
		if('='==ch||'\r'==ch||'+'==ch||'-'==ch)
		{
			/***********************************************************/
			tcnarr[tcna_i]=atoi(tnsarr);//将*号前的数字赋给临时整型数组
			++tcna_i;
			
			/***********************************************************/
			int i;
			tfn=tcnarr[0];
			//printf("\n此时的tcna_i=%d\n",tcna_i);
			for(i=0;i<tcna_i;++i)
			{
			//	printf("\n此时的符号=%c\n",csarr[i]);
				if('*'==csarr[i])
					{
				//		printf("\n此时的tfn=%d\n",tfn);
						
				//		printf("\n此时的tcnarr[i]=%d\n",tcnarr[i]);
				//		printf("\n此时的tcnarr[i+1]=%d\n",tcnarr[i+1]);
						
					tfn*=tcnarr[i+1];
					}
				if('/'==csarr[i])
					tfn/=tcnarr[i+1];
			}
			isj=1;
			break;
		}
	}
	 // printf("tfn=%d",tfn);
		numarr[num_i]=tfn;
		++num_i;
		inic();//初始化乘除操作
		//printf("\n执行zuihou\n");
		return;
}


/*处理数字*/
void setNumberstr(char c){
	printf("%c",ch);
	tnsarr[tnsa_i]=c;
	++tnsa_i;
	
	return;
}


//初始化临时数字字符串数组
void iniTsarr()
{
	tnsa_i=0;
	memset(tnsarr,'\0',30*sizeof(char));
	return;
}

//计算结果
void finish()
{
	int i=0;
	fn=numarr[0];
//	printf("\n执行finish\n");
	for(i=0;i<num_i;++i)
	{

		
		if('+'==jsarr[i])
		{
	//		printf("加\n");
			//printf("此时的number%d\n",numarr);
		//	printf("此时的numarr[i]%d\n",numarr[i]);
		//	printf("此时的numarr[i+1]%d\n",numarr[i+1]);
			fn+=numarr[i+1];
		}
		if('-'==jsarr[i])
		{
		//	printf("减\n");
			//printf("此时的number%d\n",number);
		//	printf("此时的numarr[i]%d\n",numarr[i]);
	//		printf("此时的numarr[i+1]%d\n",numarr[i+1]);
			fn-=numarr[i+1];
		}
		
	}
	return;	
}


void iniAll(void)
{
	memset(numarr,0,sizeof(int)*30);//存放最终计算的数字的数组(Number array)
	num_i=0;//(Number index)
	fn=0;//存放最终的结果(finish number)
	memset(tnsarr,'\0',sizeof(char)*30);//存放数字字符的临时字符串数组(Temporary Number String Array)
	tnsa_i=0;//上面数组的下标(Temporary number string array index)
	memset(jsarr,'\0',sizeof(char)*30);//存放+-字符的临时字符串数组(jia/jian string array)
	jsa_i=0;//上面数组的下标(jia/jian string array index)
	//int t_num_array[30];//存放数字字符的临时字符串数组
	//int t_num_index=0;//上面数组的下标
	memset(csarr,'\0',sizeof(char)*30);//存放*/字符的临时字符串数组(cheng/chu string array)
	csa_i=0;//上面数组的下标(cheng/chu string array index)
	
	isj=0;

	
	return;
}
//初始化乘除操作
void inic()
{
	memset(tcnarr,0,sizeof(int)*30);//存放乘除数字的临时整型数组(Temporary cheng/chu number array)
	tcna_i=0;//上面数组的下标(Temporary cheng/chu number array index)
	memset(csarr,0,sizeof(char)*30);//存放*/字符的临时字符串数组(cheng/chu string array)
	csa_i=0;//上面数组的下标(cheng/chu string array index)
	tfn=0;
	return;
	}
	