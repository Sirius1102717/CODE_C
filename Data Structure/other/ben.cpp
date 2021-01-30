#include<stdio.h>
#include<string.h>
int main(void)
{
   int hh;
   int mm;
   char none;
   while(scanf("%d%c%d",&hh,&none,&mm)!=EOF)
   {if(hh < 12)
   {
       if(hh < 10)
       {
           if(mm < 10)
           printf("Only 0%d:0%d.  Too early to Dang.",hh,mm);
           else
           {
               printf("Only 0%d:%d.  Too early to Dang.",hh,mm);
           }
       }
       else
       {
           if(mm < 10)
           printf("Only 0%d:0%d.  Too early to Dang.",hh,mm);
           else
           {
               printf("Only 0%d:%d.  Too early to Dang.",hh,mm);
           }
       }
   }
   else if(hh ==12 && mm == 0)
   printf("Only 12:00.  Too early to Dang.");
   else
   {
       int i=0;
       if(mm != 0)
       { 
           for(i;i < hh-11;i++)
           printf("Dang");
           printf("\n");
       }
       else
       {
           for(i;i < hh-12;i++)
           printf("Dang");
           printf("\n");
       }
   }}
   
}