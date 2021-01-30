#include<stdio.h>
//#include<string.h>
int a[100] = {0},b[10000] = {0},as[10000] = {0};
int main(void){
    int n,k[100] = {0},i,j;
    int m,counter = 0,judge = 0;
    int asn = 0;
    scanf("%d",&n);
    for(i = 0 ; i < n ;i++){
        scanf("%d",&k[i]);
        counter += k[i];
        for(j = counter - k[i] ; j < counter ; j++)
            scanf("%d",&a[j]);
    }
    for(i = 0 ; i < counter ; i++){
    //printf("%s ",a[i]);
        scanf("%d",&m);
        for(i = 0 ; i < m ; i++){
            scanf("%d",&b[i]);
            for(j = 0 ; j < counter ; j++){
                if(b[i] == a[j] || b[i] == as[j])
                    break;
                else
                    judge++;
        }
            if(judge == counter){
                as[asn] = b[i];
                asn++;
            }
            judge = 0;
        }
    }
    if(asn == m)
        printf("No one is handsome");
    else{
        for(i = 0 ; i < asn ;i++)
        printf("%05d ",as[i]);
    }
}