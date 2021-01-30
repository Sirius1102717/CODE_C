#include<stdio.h>
#include<string.h>
#define N 3
struct student{
    int num;
    char name[20];
    int score;
}stu[N],p;
int main(void){
    int i,len;
    char new[20],judge[20];
    FILE *fp = fopen("stu.txt","w");
    FILE *rp;
    for(i = 0 ; i < N ; i++){
        scanf("%d%s%d",&stu[i].num,stu[i].name,&stu[i].score);
        fprintf(fp,"%d\t%s\t%d\n",stu[i].num,stu[i].name,stu[i].score);
    }
    fclose(fp);
    rp = fopen("stu.txt","r+");
    printf("Please input the name you want to change\n");
    scanf("%s",judge);
    len = strlen(judge);
    //for(i = 0 ; i < N ; i++){
        while(fscanf(rp,"%d%s%d",&p.num,p.name,&p.score) != EOF){
        if(strcmp(judge,p.name) == 0){
            fseek(rp,-len-3,SEEK_CUR);
            printf("Please input the new name\n");
            scanf("%s",new);
            fprintf(rp,"%s",new);
            break;

        }
    }
    fclose(rp);
}