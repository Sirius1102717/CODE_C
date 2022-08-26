/*
 * @Author: Freaver
 * @Date: 2021-01-25 12:29:56
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-26 12:41:40
 */

#include<bits/stdc++.h>
using namespace std;

int person[100];

void init(int *friendGroup, int n)
{
    int i;
    for ( i = 1; i <= n; i++ ) {
        friendGroup[i] = i;
    }
}

int getFriend(int *friendGroup, int v)
{
    if ( friendGroup[v] == v)
        return v;
    
    return friendGroup[v] = getFriend(friendGroup, friendGroup[v]);
}

void fmerge(int *friendGroup, int xi, int yi)
{
    int t1 = getFriend(friendGroup, xi);    
    int t2 = getFriend(friendGroup, yi);    

    if ( t1 != t2)
        friendGroup[t2] = t1;
}

void print(int *friendGroup, int a, int b)
{
    if ( friendGroup[a] == friendGroup[b] )
        cout << "yes" << "\n";
    else
        cout << "no" << "\n";
}

int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;
    int friendGroup[10] = {0};
    init(friendGroup, n);
    int i;
    int xi, yi;
    int a, b;
    for ( i = 0; i < m; i++ ) {
        cin >> xi >> yi;
        fmerge(friendGroup, xi, yi);
    }
    for ( i = 0; i < k; i++ ) {
        cin >> a >> b;
        print(friendGroup, a, b);
    }

    for ( auto j : friendGroup )
        cout << j << " ";
    return 0;
}
