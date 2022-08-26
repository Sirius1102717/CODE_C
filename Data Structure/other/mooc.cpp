#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int BinarySearch(int a[], int left, int right, int b) {
  int half = (right + left) / 2, as = 0;
  if (b == a[half])
    return half + 1;
  else if (b > a[half]) {
    left = half + 1;
    BinarySearch(a, left, right, b);
  } else if (b < a[half]) {
    right = half;
    BinarySearch(a, left, right, b);
  }
}
int main(void)
{
    int a[] = {1, 2, 3};
    int b, left = 0, right = 3;
    for (b = 1; b < 8; b++)
    {
        int c = printf("%d ", BinarySearch(a, left, right, b));
    }
}
/*#include <stdio.h>
#include<string.h>
int main(void)
{
    char a[100]={0},b[100]={0};
    gets(a);
    int n=strlen(a),i,j=1;
    b[0]=a[0]-32;
    for(i=1;i<n;i++)
    {
        b[j]=a[i];
        if(a[i]==' '&&a[i+1]==' ')
            continue;
        else if(a[i-1]==' '&&a[i]!=' ')
        b[j]=a[i]-32;
        j++;
    }
    puts(b);
}*/