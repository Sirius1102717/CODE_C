#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
long long llatoi(char *s)
{
    int len = strlen(s);
    long long num = 0;
    for(int i = len-1 ; i >= 0 ;i--)
    num += (*(s+i)-48) * pow(10,len - i - 1);
    return num;
}
int myAtoi(char * s){
int lennums = 0,sign = 0,i,j;
long long num = 0;
int len = strlen(s);
char nums[100] = {0};
for(i = 0;i < len ; i++)
{
    if(*(s+i) == '-')
    {
        sign++;
        break;
    }
    else if(*(s+i) >= '0' && *(s+i) <= '9')
    {
        nums[lennums] = *(s+i);
        lennums++;
    }
    else if((*(s+i) < '0' || *(s+i) >'9') && (*(s+i) != ' ') &&(*(s+i) != '"') && (*(s+i) != '+'))
    break;
    else if(*(s+i) == '+')
    {
        if((*(s+i+1) < '0' || *(s+i+1) >'9') && (*(s+i+1) != ' '))
        break;
    }
    n++;
}
for(j = i ; j < len ;j++)
{
    if(*(s+j) >= '0' && *(s+j) <= '9')
    {
        nums[lennums] = *(s+j);
        lennums++;
    }
    else if((*(s+j) < '0' || *(s+j) >'9') && (*(s+i) != ' ') &&(*(s+j) != '"'))
    break;
}
num = llatoi(nums);
if(num > 2147483648)
num = 2147483648;
if(sign == 0)
return num;
else return num = -num;
}
int main(void)
{
char *s ="    -42";
printf("%d",myAtoi(s));
}