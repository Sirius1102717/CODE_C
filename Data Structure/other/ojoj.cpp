#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    char c,arr[20][20] = {0};
    int i,j,arrlen[20] = {0},n = 0;
    while(1)
    {
        c = getchar();
        if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
            {
                arr[n][arrlen[n]] = c;
                arrlen[n]++;
            }
        if(c == '\n')
        break;
        if(c == ' ') 
            n++;
    }
    for(i = n;i >= 0;i--)
        {
            if(arrlen[i] != 0)
            {
                for(j = 0;j <= arrlen[i];j++)
                printf("%c",arr[i][j]);
               // printf(" ");
            }
        }
}
