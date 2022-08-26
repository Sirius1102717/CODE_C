#include<stdio.h>
int main()
{
    FILE *fp;
    int number;
    char name[20];
    double pay;
    char filename[80];
    printf("Input file name\n");
    scanf("%s",filename);
    fp = fopen(filename,"w");
    if(fp != NULL)
    {
        for(int i = 1 ; i <= 4 ; i++)
        {
            fscanf(stdin,"%d %s %lf",&number,name,&pay);
            fprintf(fp,"%d %s %.2f\n",number,name,pay);
        }
        fclose(fp);
    }
    return 0;


    }