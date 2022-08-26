#include<stdio.h>
#include<string.h>

char *print(int n,char t, char ft,char tt)
{
    char as[20] = {0};
    char *pas = &as;
    if(n < 4)
    {
        for(int i = 0; i < n ;i++)
        *(pas+i) = t;
    }
    else if(n == 4)
    {
        *(pas+0) = t;
        *(pas+1) = ft;
    }
    else if(n == 5)
    *pas = ft;
    else if(n > 5 && n < 9)
    {
        //printf("%c",ft);
        *pas = ft;
        for(int i = 0 ; i < n-5 ; i++)
        //printf("%c",t);
        *(pas+i+1) = t;
    }
    else if(n == 9)
    {
        //printf("%c%c",t,tt);
        *(pas+0) = t;
        *(pas+1) = tt;
    }
    return pas; 
}
int main(void)
{
    int n,j;
    char M = 'M', D = 'D', C = 'C', L = 'L', X = 'X', V = 'V', I = 'I';
    char *as;
    scanf("%d",&n);
    int m = n / 1000;
    //int d = (n - 1000*m) % 500;
    int c = (n - 1000*m ) / 100;
    //int l = (n - 1000*m - 500*d - 100*c) % 50;
    int x = (n - 1000*m - 100*c) / 10;
    //int v = (n - 1000*m - 100*c - 10*x) % 5; 
    int i = (n - 1000*m - 100*c - 10*x);
    //printf(""");
    if(m > 0)
    {
        char as0[5] ={0};
        for(int j = 0 ; j < m ;j++)
        as0[j] = 'M';
        //printf("M");
        strcat(as,as0);
    }
    if(c > 0)
    {
        char *as1 = print(c,C,D,M);
        strcat(as,as1);
    }
    if(x > 0)
    {
        char *as2 = print(x,X,L,C);
        strcat(as,as2);
    }
    if(i > 0)
    {
        char *as3 = print(i,I,V,X);
        strcat(as,as3);
    }
    printf("%s",as);

}