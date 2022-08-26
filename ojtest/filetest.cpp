#include<stdio.h>
#include<stdlib.h>

int MemberNumber = 1;

typedef struct member {
    int num;
    char name[20];
    int age;
}MEMBER;
MEMBER mem1[10],mem[10],mem2[10];

int numLenJudge(int num){
    int len = 0;
    while(1){
        if(num == 0)
            break;
        else{
            num /= 10;
            len++;
        }
    }
    return len;
}

int main(void){
    FILE *fp1 = fopen("file1.txt","w");
    FILE *fp2 = fopen("file2.txt","w");
    int i;
    for( i = 0 ; i < 5 ; i++ ){
        scanf("%d%s%d",&mem[i].num,mem[i].name,&mem[i].age);
        fwrite(&mem[i],sizeof(MEMBER),1,fp1);
        fprintf(fp2,"%d\t%s\t%d\n",mem[i].num,mem[i].name,mem[i].age);
    }
    for( i = 0 ; i < 5 ; i++ ){
       fscanf(fp1,"%d%s%d",&mem1[i].num,mem1[i].name,&mem1[i].age);
       fread(&mem2[i],sizeof(MEMBER),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    FILE *fp3 = fopen("file1.txt","r");
    FILE *fp4 = fopen("file2.txt","r");
    for( i = 0 ; i < 5 ; i++ ){
       fscanf(fp4,"%d%s%d",&mem1[i].num,mem1[i].name,&mem1[i].age);
       fread(&mem2[i],sizeof(MEMBER),1,fp3);
    }
    for( i = 0 ; i < 5 ; i++ )
        printf("%d %s %d\n",mem1[i].num,mem1[i].name,mem1[i].age);
    for( i = 0 ; i < 5 ; i++ )
        printf("%d %s %d\n",mem2[i].num,mem2[i].name,mem2[i].age);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
