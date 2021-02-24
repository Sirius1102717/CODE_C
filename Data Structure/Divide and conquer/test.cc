#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &a, int low, int mid, int high)
{
    int *b = new int[high - low + 1];
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high)
        if (a[i] <= a[j]) {
            b[k] = a[i];
            i++;
            k++;
        } else {
            b[k] = a[j];
            j++;
            k++;
        }
    while (i <= mid)  // 将第1 段余下部分复制到b
    {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= high)  // 将第2 段余下部分复制到b
    {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k = 0, i = low; i <= high; k++, i++)  // 将b 复制回a中
        a[i] = b[k];
    delete[] b;
}
void mergepass(vector<int> &a, int length, int n)
{  // length表示每个片段的段长度
    int i;
    for (i = 0; i + 2 * length - 1 < n;
         i += 2 * length) {  //归并长度为length的两个子序列
        merge(a, i, i + length - 1, i + 2 * length - 1);
    }
    if (i + length - 1 < n)  //最后的子表长度可能小于length
        merge(a, i, i + length - 1, n - 1);
}
void merge_sort(vector<int> &a, int n)
{
    int length;
    for (length = 1; length < n; length = 2 * length) {  // log2(n)趟
        mergepass(a, length, n);
    }
}
int main( )
{
    vector<int> data{61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62};
    int n = data.size( );
    // SI_sort(data,n);
    // shell_sort(data,n);
    // Bibble_sort(data,n);
    // quickSort(data,0,n-1);
    // select_sort(data,n);
    // head_sort(data,n);
    merge_sort(data, n);
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    return 0;
}