#include<stdio.h>
#include<string.h> 
int main(void) 
{
	int a,b,c,i,j,n=0;
	char as[100][100][100]={0};
    int p[100]={0},no[100]={0},l=0,as1=0;
	while(scanf("%d%d%d",&a,&b,&c)!=EOF) 
	{
        char a1[100][100]={0};
	    char b1[100][100]={0};
	    char c1[100][100]={0};
		fflush(stdin);
		for(i=0;i<a;i++)
        scanf("%s",a1[i]);
        fflush(stdin);
		for(i=0;i<b;i++)
        scanf("%s",b1[i]);
        fflush(stdin);
        for(i=0;i<c;i++)
        scanf("%s",c1[i]);
        for(i=0;i<a;i++)
        {
            if(strcmp(a1[i],b1[i])==0&&strcmp(a1[i],c1[i])!=0)
            {
                strcpy(as[l][n],a1[i]);
                //n++;
            }
        }
        puts(as[l][n]);

		/*if(n!=0) 
		{
            p[l]++;
		} else 
		{
			no[l]=1;
		}
        l++;
	}
    for(i=0;i<l;i++)
    {
        if(p[l]!=0)
        {
            for(j=0;j<n;j++)
            printf("%s ",as[l][n]);
        }
        else if(no[l]==1)
        printf("No enemy spy\n");
        l++;*/
    }
}
