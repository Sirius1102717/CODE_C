#include<stdio.h>
int maxcm(int a,int b)
{
    int m,n,i;
    if(b>a)
    {
        m=a;
        a=b;
        b=m;
    }
   for(i=1;i<=b;i++)
    {
        if(b%i==0&&a%i==0)
            n=i;
    }
    return n;
}
int maxcd(int a,int b)
{
    int n,m,i;
    if(b>a)
    {
        m=a;
        a=b;
        b=m;
    }
   for(i=1;i<=b;i++)
    {
        if(b%i==0&&a%i==0)
            n=i;
    }
    return n=a*b/n;

}
int main(void)
{
   int a,b,n,m;
   scanf("%d%d",&a,&b);
   n=maxcm(a,b);
   m=maxcd(a,b);
    printf("%d %d",n,m);
}
