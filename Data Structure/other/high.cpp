#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int max(int a,int b)
{
    int m;
    return m=a>b?a:b;
}
/*int main(void)
{
    char sa[10000],sb[10000],c[10000]={0};
    int a[10000]={0},b[10000]={0};
    int lena,lenb,i;
    scanf("%s",sa);
    scanf("%s",sb);
    lena=strlen(sa);
    lenb=strlen(sb);
    for(i=0;i<lena;i++)
    a[lena-i-1]=sa[i]-'0';
    for(i=0;i<lenb;i++)
    b[lenb-i-1]=sb[i]-'0';
    int maxlen=max(lena,lenb);
    for(i=0;i<maxlen;i++)
    {
        c[i]=c[i]+a[i]+b[i];
        c[i+1]=c[i]/10;
        c[i]%=10;
    }
    while(c[maxlen]==1) maxlen++;
    for(i=maxlen-1;i>=0;i--)
    printf("%d",c[i]); 
}*/
/*int main(void)
{
    char sa[10000],sb[10000];
    int a[10000],b[10000],c[10000];
    scanf("%s%s",sa,sb);
    int lena=strlen(sa),lenb=strlen(sb),i;
    if(lenb>lena||(lena==lenb&&sb>sa))
    {
        printf("-");
        swap(sa,sb);
        swap(lena,lenb);
    }
    for(i=0;i<lena;i++)
    a[i]=sa[lena-i-1]-'0';
    for(i=0;i<lenb;i++)
    b[i]=sb[lenb-i-1]-'0';
    lena=max(lena,lenb);
    for(i=0;i<lena;i++)
    {
        c[i]=c[i]+a[i]-b[i];
        if(c[i]<0) c[i]=c[i]+10,c[i+1]=-1;
    } while(c[lena-1]==0&&lena>0) lena--;
    for(int i=lena-1;i>=0;i--) printf("%d",c[i]);
}*/
int main(void)
{
    char sa[10000],sb[10000];
    int a[10000],b[10000],i,c[10000];
    scanf("%s%s",sa,sb);
    int lena=strlen(sa);
    int lenb=strlen(sb);
    for(i=0;i<lena;i++)
    a[i]=sa[lena-1-i]-'0';
    for(i=0;i<lenb;i++)
    b[i]=sb[lenb-1-i]-'0';
    int lenc=lena+lenb-1,j;
    for(i=0;i<lena;i++)
    {
        for(j=0;j<lenb;j++)
        {
            c[i+j-1]+=a[i]*b[j];
            c[i+j]+=c[i+j-1]/10;
            c[i+j-1]%=10;
        }
    }
    while(c[lenc]>0)lenc++;
    for(i=lenc-1;i>=0;i--)
    printf("%d",c[i]);

}