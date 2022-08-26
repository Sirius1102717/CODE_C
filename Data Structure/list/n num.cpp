#include<stdio.h>
#define ll long long
int main(){
    int n,i;
    char c;
    ll a[100] = {0},b[100] = {0};
    double as = 0;
    ll asn = 0;
    scanf("%d",&n);
    fflush(stdin);
    for( i = 0 ; i < n ; i++ ){
        scanf("%c",&c);
       //printf("%c",c);
        if(c == '-'){
            scanf("%lld%c%lld",&a[i],&c,&b[i]);
            as -= a[i] / b[i];
        }
        else{
            a[i] = c -'48';
            scanf("%c%d",&c,&b[i]);
            as += a[i] / b[i];
        }
    }
    asn = (ll)as;
    as -= asn;
    //if(asn != 0)
        printf("%lld ",asn);
    printf("%lf",as);        
}