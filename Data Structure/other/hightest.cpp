#include <stdio.h>
#include <string.h>
#define MAXLEN 210
#define N 1000
void Invert(char *a,int *b)
{
 int len=strlen(a),j=0;
 for(int i=len-1;i>=0;i--)
 {
  b[j++]=a[i]-'0';
 }
}
char[] highplus(char str1[],char str2[])
{
 char str[MAXLEN];
 int a[MAXLEN],b[MAXLEN],c[MAXLEN];//存放加数以及和的整型数组（中间处理） 
 printf("输入两个加数：\n");
 //整型数组a,b,c的元素全部清零,memset函数一般用于在对定义的字符串进行初始化为"\0"，对较大的结构体或数组进行清0操作的一种最快方法 
 memset(a,0,sizeof(a));
 memset(b,0,sizeof(b)); 
 memset(c,0,sizeof(c));
 //将两个加数字字符串按位逆置存放到整型数组中，下标0对应个位
 Invert(str1,a);
 Invert(str2,b);
 int len=strlen(str1)>=strlen(str2) ? strlen(str1):strlen(str2);//求加数较长的位数
 for(int i=0;i<len;i++)//从第一位到最高位逐位相加运算 
 {
  c[i]+=a[i]+b[i];
  c[i+1]=c[i]/10;//c[i]能除多少个10就表示进多少个位，i位的进位数存放到c[i+1]上
  c[i]%=10; //c[i]进完位后的数则是(a[i]+b[i])求模10，为余下的数 
 } 
 while(len >= 0 && c[len] == 0)//和的处理，去掉前导0，并把结果复制到串中
 {
  len--;
 } 
 memset(str,0,sizeof(str));//0<=>'\0'字符串结束符 
 int i=0;
 for(int j=len;j>=0;j--)
 {
  str[i++]=c[j]+'0';//整型数字转换为字符型数字 
 } 
  if(strlen(str)==0)
 {
  str[0]='0';//结果为0的情况 
 }
 return str;
} 
char[] highsubstract(char sa[],char sb[])
{
    char sc[202];
    int a[202],b[202],c[202];
 int alen=strlen(sa),blen=strlen(sb),len;
 char cfh='+';//存放结果正负符号 
 if(alen==blen&&strcmp(sa,sb)==0)//被减数等于减数的情况 
 {
  printf("0\n"); 
  return 0;
 }
 else if(alen<blen||alen==blen&&strcmp(sa,sb)<0)//①减数的位数大于被减数或者②两数位数相等，减数大于被减数 
 {
  char st[202];//临时字符串数字，用于交换char sa与char sb
  strcpy(st,sa);strcpy(sa,sb);strcpy(sb,st); //保证字符数组sa的位数始终是最大的位数 
  cfh='-';
 }
 alen=strlen(sa);blen=strlen(sb);
 for(int i=0;i<alen;i++)
 {
  a[i]=sa[alen-1-i]-'0';//将char sa[]逆置存放到int a[]中 
 }
 for(int i=0;i<blen;i++)
 {
  b[i]=sb[blen-1-i]-'0';
 }
 for(int i=0;i<alen;i++)//开始对int a[],b[],c[]逐位进行减法运算 
 {
  c[i]=c[i]+a[i]-b[i];
  if(c[i]<0)//处理退位 
  {
   c[i]+=10;
   c[i+1]--;
  }
 }
 int i=alen-1;//将结果去掉前导0后存放到sc中
 while(c[i]==0)
 {
  i--;
 }
 int j=0;
 while(i>=0)
 {
  sc[j++]=c[i]+'0';
  i--;
 }
 sc[j]='\0';//字符串单个赋值不会自动加上字符串结束符'\0'，如果之前有memset(sc,0,sizeof(sc))，则不需要该行语句
 if(strlen(sc)==0)
 {
  return sc;
 } 
 else
 {
   for(i = 0;i<alen;i++)
 }
}
void Output(int *p,int len);//输出整型数组元素 
void Invert(char *a,int *b);//将a字符逆置转换到整数数组b中，确保下标0对应个位而不是最高位 
char str1[MAXLEN],str2[MAXLEN],str[2*MAXLEN];//存放乘数字符串以及乘积对应的字符串
int a[MAXLEN],b[MAXLEN];//存放运算时乘数的各个位
int c[2*MAXLEN];//存放运算后乘积的各个位
int main(void)
{
 printf("请输入两个乘数：\n");
 scanf("%s %s",str1,str2);//以字符串的形式输入两个乘数 
 int len1=strlen(str1),len2=strlen(str2);
 /*确定乘积的符号 */
 int sign=1,k=0;//sign标识结果的正负，k用于将字符串首地址向后移动k位 
 memset(a,0,sizeof(a));//整型数组a,b清0 
 memset(b,0,sizeof(b));//整型数组a,b清0  
 if(str1[0]=='-')
 {
  len1--;
  sign*=-1;
  k++;
 } 
 Invert(str1+k,a);
 k=0;
 if(str2[0]=='-')
 {
  len2--;
  sign*=-1;
  k++;
 } 
 Invert(str2+k,b);
 /*确定乘积的符号 */
// Output(a,len1);
// Output(b,len2); 
 /*逐位运算，没有处理进位*/
 memset(c,0,sizeof(c));
 for(int i=0;i<len2;i++)
 {
  for(int j=0;j<len1;j++)
  {
   c[i+j]+=a[j]*b[i];
  } 
 }
 /*逐位运算，没有处理进位*/
 /*处理进位*/
 for(int i=0;i<len1+len2;i++)
 {
  c[i+1]+=c[i]/10;
  c[i]%=10;
 }
 /*处理进位*/
 /*结果处理，将最高位(len1+len2-1)前导0去掉后，转换成字符存储到积串str中*/
 int i=len1+len2-1,j=0;
 while(c[i]==0)
 {
  i--;
 }
 memset(str,0,sizeof(str));
 for(;i>=0;i--)
 {
  str[j++]=c[i]+'0';//整型数字转换为字符型数字 
 }
 /*结果处理，将最高位(len1+len2-1)前导0去掉后，转换成字符存储到积串str中*/ 
 /*输出运算结果*/
 if(strlen(str)==0)//结果为0的情况 
 {
  str[0]='0';
 }
 printf("%s * %s = ",str1,str2);
 if(sign==-1)
 {
  printf("-");
 }
 printf("%s \n",str);
 /*输出运算结果*/
 return 0;
}  
void Invert(char *a,int *b)
{
 int len=strlen(a),j=0;
 for(int i=len-1;i>=0;i--)
 {
  b[j++]=a[i]-'0';
 }
}
void Output(int *p,int len)
{
 for(int i=0;i<len;i++)
 {
  printf("%d",p[i]);
 }
}
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define N 3000
int result[N];//存放n!值的各个位上的数，result[0]存放个位 
int main(void)
{
 int n;//存放n 
 printf("计算n!,输入n的值：");//提示输入n
 scanf("%d",&n);
 memset(result,0,N);
 result[0]=1;//累乘器初始化赋值为1
 int digits=1;//存放结果的位数，初始化时位数为1
 for(int i=2;i<=n;i++)//i存放每次阶乘的操作数（1*2*3...*n） 
 {
  int jw=0;//jw存放低位向高位的进位数
  for(int j=0;j<digits;j++)//将result从个位起至第digits位依次乘以i 
  {
   int total=result[j]*i+jw;
   result[j]=total%10;//int result[0]存放运算结果的个位，result[1]存放十位 
   jw=total/10;
   if(j==digits-1&&jw)
   {
    digits++;
   }
  } 
 }
 char factarr[N];//存放result的字符串
 memset(factarr,0,N);
 for(int i=digits-1,j=0;i>=0;i--)
 {
  factarr[j++]=result[i]+'0';//int result[]转换为char factarr[]，并且char factarr[0]存放运算结果最高位.... 
 }
 printf("%d!=%s\n",n,factarr);//输出n!= factarr
 return 0;
} 
#include <stdio.h>
#include <string.h>
#define MAXLEN 1010
char str1[MAXLEN];//以字符串存放高精度被除数
int main(void)
{
	int b;//存放低精度除数
	printf("请输入被除数和除数：\n");
	scanf("%s %d",str1,&b);
	int a[MAXLEN],c[MAXLEN];//元素值分别存放被除数以及商的各个位对应整数
	memset(a,0,sizeof(a));//数组元素值初始化为0 
	memset(c,0,sizeof(c));//数组元素值初始化为0 
	int len1=strlen(str1);
	for(int i=0;i<len1;i++)
	{
		a[i]=str1[i]-'0';//将被除数str1的数值，按各个位转换为整型对应存放到整型数组a[]中 ,a[0]为最高位 
	}
	int x=0;//存放每次做除法时的被除数 
	for(int i=0;i<len1;i++)//从高位向低位按位相除,"按位相除法"四行代码搞定 
	{
		c[i]=(x*10+a[i])/b;
		x=(x*10+a[i])%b;
	}
	//删除商前导0，将商存放到串中并输出式子以及商
	int len=0;
	while(c[len]==0&&len<len1)
	{
		len++;
	} 
	char str[MAXLEN];//存放字符串类型的商
	memset(str,0,sizeof(str));
	for(int i=len,j=0;i<len1;i++)
	{
		str[j++]=c[i]+'0';
	} 
	printf("%s / %d = %s\n",str1,b,str);
	return 0;
} 