void swap(int *a, int *b)    
{  
    int temp;  
    temp = *a;  
    *a = *b;  
    *b = temp;  
}
void QuickSort(int *arr, int begin, int end)  
{  
    int i,j;
    if(begin<end)
    i=begin+1;
    j=end;
    while (i<j)
    {
        if(arr[i]>arr[j])
        swap(&arr[i],&arr[j]);
        j--;
    }
    else
    i++;
    if(i>=end)
    i--;
    QuickSort(arr,begin,i);
    QuickSort(arr,j,end);
}
//void BinarySort(int arr[])
{
    int moddle=n/2,left=1,right=n,i,j;
    for(i=n;i<=n;i++)
    {
        for(j=i;i<=n-i-1;j++)
        {
            if(arr[j]>arr[moddle])
            {
                int temp=arr[j];
                arr[j]=arr[moddle];
                arr[moddle]=temp;
            }
        }
    }
    {
        
    }
}//
void Merge(int a[], int left, int mid, int right)
{
    int i,temp=[left+right-1];
    for(i=left;i<=right;i++)
       temp[i-left]=a[i];
    int i=left,j=mid+1,k=left;
    for(k;k<=right;k++)
    {
        if(i>mid&&j<=right)
           a[k]=temp[j-left];j++;
        else if(j>right&&i<=mid)
           a[k]=temp[i-left];i++;
        else if(temp[i-left]>temp[j-left])
           a[k]=temp[j-left];j++;
        else if(temp[i-left]<=temp[j-left])
           a[k]=temp[i-left];i++;
    }
    for(i=left;i<=right;i++)
    printf("%d ",a[i]);
}
void Mergesort(int a[],int left,int right)
{
    if(left>=right)
    return;
    int mid=(right+left)/2;
    Mergesort(a,left,mid);
    Mergesort(a,mid+1,right);
    Merge(a,left,mid,right);
}   
void ogsearch(int grade,int stunum[],char name[][20],int option[],int test[],int must[],int avergrade[],char rank[])
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(grade==option[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    }
}
void tgsearch(int grade,int stunum[],char name[][20],int option[],int test[],int must[],int avergrade[],char rank[])
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(grade==test[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    }
}
void mgsearch(int grade,int stunum[],char name[][20],int option[],int test[],int must[],int avergrade[],char rank[])
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(grade==must[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    }
}
void agsearch(int grade,int stunum[],char name[][20],int option[],int test[],int must[],int avergrade[],char rank[])
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(grade==avergrade[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    }
}
/*void gradesearch(char name[][20],int option[],int test[],int must[],int avergrade[],char rank[],int stunum[])
{
    printf("Please choose your search way:\noption:1\ntest:2\nmust:3\navergrade:4\n");
    int a,i;
    scanf("%d",&a);
    switch (a)
    {
    case 1:for(i=1;i<=n;i++)
    {
        if(grade==option[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    } break;
    case 2:for(i=1;i<=n;i++)
    {
        if(grade==test[i])
        {
             print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    } break;
    case 3:for(i=1;i<=n;i++)
    {
        if(grade==must[i])
        {
            print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    } break;
    default:for(i=1;i<=n;i++)
    {
        if(grade==avergrade[i])
        {
            print(name[n],option,test,must,avergrade,rank,stunum,i);
        }
    } break;
    }
}*/
int change(char name[][20],int option[],int test[],int must[],int stunum[]){
    int choice;
    int num;
    int goal=0;
    printf("please enter the student's number:");
    scanf("%d",&num);
    for (int j = 1; j <= n; j++)
    {
        if (stunum[j]==num)
        {
            num=j;
            break;
        }
        
    }
    printf("please enter the record you want to change:\noption grade:1\ntest grade:2\nmust grade:3\n");
   
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
    printf("you want to change it to:");
    scanf("%d",&goal);
    option[num]=goal;
    break;
    case 2:
    printf("you want to change it to:");
    scanf("%d",&goal);
    test[num]=goal;
    break;
    case 3:
    printf("you want to change it to:");
    scanf("%d",&goal);
    must[num]=goal;
    break;
    
    default:
        break;
    }
    return num;
    
}
void rangesort(char name[][20],int option[],int test[],int must[],int avergrade[],char rank[],int stunum[])
{
    printf("Please choose your choice:\noption:1\ntest:2\nmust:3\navergrade:4\n");
    int choose,min,max,i;
    scanf("%d",&choose);
    printf("Please input the mingrade:");
    scanf("%d",&min);
    printf("Please input the maxgrade:");
    scanf("%d",&max);
    switch(choose)
    {
        case 1:for(i=1;i<=n;i++)
        {
            if(option[i]>=min&&option[i]<=max)
            print(name,option,test,must,avergrade,rank,stunum,i);
        }
        case 2:for(i=1;i<=n;i++)
        {
            if(test[i]>=min&&test[i]<=max)
            print(name,option,test,must,avergrade,rank,stunum,i);
        }
        case 3:for(i=1;i<=n;i++)
        {
            if(msut[i]>=min&&must[i]<=max)
            print(name,option,test,must,avergrade,rank,stunum,i);
        }
        default:for(i=1;i<=n;i++)
        {
            if(avergrade[i]>=min&&avergrade[i]<=max)
            print(name,option,test,must,avergrade,rank,stunum,i);
        }
        
    }
}
