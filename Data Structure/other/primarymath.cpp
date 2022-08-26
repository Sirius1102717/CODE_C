#include<stdio.h>
#define ll long long
ll dpow(ll base, ll power) {
    ll result = 1;
    while (power > 0) {
        if (power & 1) {//此处等价于if(power%2==1)
            result = result * base % 1000;
        }
        power >>= 1;//此处等价于power=power/2
        base = (base * base) % 1000;
    }
    return result;
}
int main(void)
{
ll t,j=0,i,as[100]={0},m=0;
    scanf("%lld",&t);
    while(j<t)
    {
        ll in[3]={0},n;
        for(i=0;i<3;i++)
        scanf("%lld",&in[i]);
        scanf("%lld",&n);
        if(in[1]==in[2])
        as[m++]=in[1]%200907;
        if(in[1]!=in[2])
        {
        if((in[1]*2)==(in[0]+in[2]))
        as[m++]=((in[0]+(in[2]-in[1])*(n-1)))%200907;
        else
        {
            as[m++]=dpow((in[2]/in[1]),n-1)%200907;
        }
        }
        j++;
    }
    for(i=0;i<t;i++)
    printf("%lld\n",as[i]);
}