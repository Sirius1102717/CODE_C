#include<stdio.h>
int prime(int b[])
{
    int a[10000]={0},i,j;
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
    }printf("%d",a[i]);

}
void primepalindrome(len)
{int d1,d2,d3,d4,palindrome[10000];
    int n=0;
    if(len<=2)
    {for (d1 = 3; d1 <= 9; d1+=2)
           palindrome[n] = d1;n++;}
            else if(len<=4)
           {
               for(d1=1;d1<=9;d1+=2)
               {
                   for(d2=1;d2<=9;d2++)
                   palindrome[n]=100*d1+10*d2+d1;
                   prime(palindrome);
                   n++;
               }
           }
           else if(len<=6)
           {
            for(d1=1;d1<=9;d1+=2)
               {
                   for(d2=1;d2<=9;d2++)
                   {
                       for(d3=1;d3<=9;d3++)
                       {
                          palindrome[n]=10000*d1+1000*d2+100*d3+10*d2+d1;
                          prime(palindrome);
                          n++;
                       }
                   }
               }
           }
           else if(len<=9)
           {
               for(d1=1;d1<=9;d1+=2)
               {
                   for(d2=1;d2<=9;d2++)
                   {
                       for(d3=1;d3<=9;d3++)
                       {
                           for(d4=1;d4<=9;d4++)
                           palindrome[n]=1000000*d1+100000*d2+10000*d3+1000*d4+d3*100+d2*10+d1;
                           prime(palindrome);
                           n++;
                       }
                   }
               }
           }
}
int main(void)
{
    int n,len;
    scanf("%d%n",&n,&len);
    primepalindrome(len);
}

