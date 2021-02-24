#include <bits/stdc++.h>
using namespace std;

void merge(int *c, int *d, int startOfFirst, int endOfFirst, int endOfSecond)
{
    int first = startOfFirst;
    int second = endOfFirst + 1;
    int result = startOfFirst;

    while ((first <= endOfFirst) && (second <= endOfSecond))
        if (c[first] <= c[second])
            d[result++] = c[first++];
        else
            d[result++] = c[second++];
    if (first > endOfFirst)
        for (int i = second; i <= endOfSecond; i++)
            d[result++] = c[i];
    else
        for (int i = first; i <= endOfFirst; i++)
            d[result++] = c[i];
}

void mergePass(int *x, int *y, int n, int segmentSize)
{
    int i = 0;
    while (i <= n - 2 * segmentSize) {
        merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
        i = i + 2 * segmentSize;
    }

    if (i + segmentSize < n)
        merge(x, y, i, i + segmentSize - 1, n - 1);
    else
        for (int j = i; j < n; j++)
            y[i] = x[i];
}

void mergeSort(int *a, int n)
{
    int *b = new int[n];
    int segmentSize = 1;
    while (segmentSize < n) {
        mergePass(a, b, n, segmentSize);
        segmentSize *= 2;
        mergePass(b, a, n, segmentSize);
        segmentSize *= 2;
    }
}

int main(int argc, char const *argv[])
{
    int a[10];
    int i;
    for (i = 0; i < 10; i++)
        cin >> a[i];
    mergeSort(a, 10);
    for (auto c : a)
        cout << c << " ";
    return 0;
}
