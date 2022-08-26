#include<stdio.h>
void Merge(int a[], int left, int mid, int right)
{
    int temp[left+right+1];
    int i;
    for(i=left;i<=right;i++)
       temp[i-left]=a[i];
       i=left;
    int j=mid+1,k=left;
    for(k;k<=right;k++)
    {
        if(i>mid&&j<=right)
        {
            a[k]=temp[j-left];
            j++;
        }
        else if(j>right&&i<=mid)
        {
            a[k]=temp[i-left];
            i++;
        }
        else if(temp[i-left]>temp[j-left])
        {
            a[k]=temp[j-left];
            j++;
        }
        else if(temp[i-left]<=temp[j-left])
        {
            a[k]=temp[i-left];
            i++;
        }
    }
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

int main(void)
{
    int a[10]={0},left=0,right=9,i;
    for(i=0;i<10;i++)
    scanf("%d",&a[i]);
    Mergesort(a,left,right);
    for(i=0;i<10;i++)
    printf("%d\n",a[i]);
}
