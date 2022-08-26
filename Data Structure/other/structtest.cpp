#include<stdio.h>
int main(void){
    int a;
    int b[1000] = {0};
    scanf("%d",&a);
    b[a]++;
    printf("%d",a);
}