#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

char c,psarr[30] ={'\0'},mdarr[30] = {'\0'},inum[30] = {0},imdas[30] = {0};
int i,j,num[30] = {0},psn = 0,mdn = 0,nnum = 0,isj = 0,tmdas[30] = {0},tmdn = 0,tmd;
int n = 0,as,m = 0;
void addnum()
{
    inum[n] = c;
    n++;
}
void ps()
{
    if(isj == 0)
    {
        num[nnum] = atoi(inum);
        nnum++;
    }
    memset(inum,0,sizeof(int)*30);
    n = 0;
    isj = 0;
    psarr[psn] = c;
    psn++;
}
void md()
{
    mdarr[mdn] = c;
    mdn++;
    tmdas[tmdn] = atoi(inum);
    tmdn++;
    mdc();
}
void reset()
{
    memset(tmdas,0,sizeof(int)*30);
    tmdn = 0;
    memset(mdarr,0,sizeof(int)*30);
    mdn = 0;
    tmd = 0;
}
void mdc()
{
    while (1)
    {
        c = getchar();
        if(c >= '0' && c <= '9')
        addnum();
        if(c == '*' || c == '/')
        md();
        if(c == '+' || c == '-' || c == ' ')
        {
           tmdas[tmdn] = atoi(imdas);
           tmdn++;
           tmd - tmdas[0];
           for(i = 0;i <= tmdn;i++)
           {
              if(psarr[i] == '*')
              tmd *= tmdas[i+1];
              if(psarr[i] == '/')
              tmd /= tmdas[i+1]; 
           }
        isj = 1;
        break;
        }
    }
    num[nnum] = tmd;
    nnum++;
    reset();
}
void finish()
{
    as = num[0];
    for(i = 0;i < nnum;i++)
    {
        if(psarr[i] == '-')
        as -= num[i+1];
        else
        as += num[i+1];
    }
}
int main(void)
{
    while((c = getchar()) != EOF)
    {
        if(c == '+' || c == '-')
        ps();
        else if(c == '*' || c == '/')
        md();
        else
        addnum();
        finish();
        printf("%d\n",as);
    }
}