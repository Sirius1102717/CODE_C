#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int a[6666],b[6666],c[6666];
int lena,lenb,lenc;
char s1[6666],s2[6666];
 
int main(){
    scanf("%s %s",s1+1,s2+1);
    lena=strlen(s1+1);
    lenb=strlen(s2+1);
    for(int i=1;i<=lena;i++) a[i]=s1[lena-i+1]-'0';
    for(int i=1;i<=lenb;i++) b[i]=s2[lenb-i+1]-'0';
    lenc=lena+lenb-1;
    for(int i=1;i<=lena;i++){
    	for(int j=1;j<=lenb;j++){
    		c[i+j-1]+=a[i]*b[j];
    		c[i+j]+=c[i+j-1]/10;
    		c[i+j-1]%=10;
		}
	}
    while(c[lenc+1]>0) lenc++;
    for(int i=lenc;i>0;i--) printf("%d",c[i]);
}