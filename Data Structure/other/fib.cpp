#include<stdio.h>
#include<string.h>
#define ll long long
int lena;
int  fib(int a)
{
    int b;
    if(a==1||a==2)
    b=1;
    else
    {
        b=fib(a-1)+fib(a-2);
    }
    return b;
}
void high(int a)
{
    char sa[10000],c[10000]={0};
    int a[10000]={0};
    int lenb,i;
    sa=fib(a);
    lena=strlen(sa);
    for(i=0;i<lena;i++)
    a[lena-i-1]=sa[i]-'0';
    //int maxlen=max(lena,lenb);
    for(i=0;i<lena;i++)
    {
        c[i]=c[i]+a[i];
        c[i+1]=c[i]/10;
        c[i]%=10;
    }
    while(c[lena]==1) lena++;
    for(i=lena-1;i>=0;i--)
    for(i=0;i<lena;i++)
    printf("%c",c[i]);
}
int main(void)
{
    int a;
    scanf("%d",&a);
    high(a);
    
}