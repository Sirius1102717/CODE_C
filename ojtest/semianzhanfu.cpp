#include<stdio.h>
int a[80][80] = {0};
int main(){
    int n,m;
    int i,j;
    long long as = 0;
    printf("%d%d",&n,&m);
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++)
        scanf("%d",&a[i][j]);
    }
    return 0;
}