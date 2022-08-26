#include<stdio.h>
int main(void)
{
    int a[10000]={0},i,j,b;
    scanf("%d",&b);
    for(i=1;i<b;i++)
    a[i]=i+1;
    for(i=1;i<b-1;i++)
    {
        for(j=i+1;j<b;j++)
        {
            if(a[j]!=0&&a[i]!=0)
            {
                if(a[j]%a[i]==0)
                {
                    a[j]=0;
                }
            }
        }
    }
    for(i=0;i<b;i++)
    {
        if(a[i]!=0)
        printf("%d\n",a[i]);
    }
}