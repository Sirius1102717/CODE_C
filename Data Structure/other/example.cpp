#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
ll poww(ll a,ll b){
    ll ans = 1, push = a;
    while(b>0){
        if(b & 1){
            ans *= push;
        }
        push *= push;
        b >>= 1;
    }
    return ans;
}
int main(void)
{
    ll t,j=0,i,as[100]={0},m=0;
    scanf("%d",&t);
    while(j<t)
    {
        ll in[3]={0},n;
        for(i=0;i<3;i++)
        scanf("%u",&in[i]);
        scanf("%u",&n);
        if(in[1]==in[2])
        as[m++]=in[1]%200907;
        if(in[1]!=in[2])
        {
        if((in[1]*in[1])==(in[0]*in[2]))
        as[m++]=poww((in[2]/in[1]),n-1)%200907;
        else
        {
            as[m++]=((in[0]+(in[2]-in[1])*(n-1)))%200907;
        }
        }
        j++;
    }
    for(i=0;i<t;i++)
    printf("%lld\n",as[i]);
}