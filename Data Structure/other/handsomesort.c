#include<stdio.h>
int as[100000],output[1000];
int asn = 0;
int main(void){
    int n,k,i,j,m;
    int input,b,on = 0;
    while(scanf("%d",&n) != EOF){
        memset(as,0,sizeof(int) * 100000);
        memset(output,0,sizeof(int) * 1000);
        on = 0;
        for(i = 0 ; i < n ; i++){
            scanf("%d",&k);
            for(j = 0 ; j < k ; j++){
                scanf("%d",&input);
                as[input]++;
        }
       }
        scanf("%d",&m);
        for(i = 0 ; i < m ; i++){
            scanf("%d",&b);
            if(as[b] == 0){
                output[on] = b;
                on++;
                as[b]++;
            }
        }
        if(on == m)
            printf("No one is handsome");
        else{
            for(i = 0 ; i < on ; i++)
                printf("%05d ",output[i]);
        }
        printf("\n");
    }
}