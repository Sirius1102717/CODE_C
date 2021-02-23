/*
 * @Author: Freaver
 * @Date: 2021-02-22 19:39:41
 * @Last Modified by: Freaver
 * @Last Modified time: 2021-02-22 19:41:04
 */

#include <bits/stdc++.h>
using namespace std;

bool minMax(int a[], int n, int &indexOfMin, int &indexOfMax)
{
    if (n < 1)
        return false;
    if (n == 1) {
        indexOfMin = indexOfMax = 0;
        return true;
    }

    int s = 1;
    if (n % 2 == 1)
        indexOfMax = indexOfMin = 0;
    else {
        if (a[0] > a[1]) {
            indexOfMax = 0;
            indexOfMin = 1;
        } else {
            indexOfMin = 0;
            indexOfMax = 1;
        }
        s = 2;
    }

    for (int i = s; i < n; i += 2) {
        if (a[i] > a[i + 1]) {
            if (a[i] > a[indexOfMax])
                indexOfMax = i;
            if (a[i + 1] < a[indexOfMin])
                indexOfMin = i + 1;

        } else {
            if (a[i + 1] > a[indexOfMax])
                indexOfMax = i + 1;
            if (a[i] < a[indexOfMin])
                indexOfMin = i;
        }
    }
    return true;
}

int main(void)
{
    int n[10] = {1, 4, 6, 2, 3, 7, 3, 8, 4, 2};
    int len = 10;
    int indexOfMin = 1;
    int indexOfMax = 1;
    minMax(n, len, indexOfMin, indexOfMax);
    for (auto c : n)
        cout << c << " ";
}