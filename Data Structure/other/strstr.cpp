#include<stdio.h>
void sortColors(int* nums, int numsSize){
int num0 = 0,num1 = 0, num2 = 0,i;
for(i = 0 ; i < numsSize ;i++)
{
    switch(*(nums+i))
    {
        case 0 :
        num0++;
        case 1:
        num1++;
        case 2:
        num2++;
    }
}
    printf("[");
    if(num0 != 0)
    {
        for(i = 0;i < num0 ;i++)
        printf("0,");
    }
    if(num1 != 0)
    {
        for(i = 0;i < num1 ;i++)
        printf("1,");
    }
    if(num2 != 0)
    {
        for(i = 0;i < num2 ;i++)
        printf("2,");
    }
    printf("]");
}
int main(void)
{
    int *nums = {2,0,2,1,1,0};
    int numSize = 6;
    sortColors(nums,numSize);
    fclose(infile);
}