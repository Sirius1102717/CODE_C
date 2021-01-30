/*
 * @Author: Freaver
 * @Date: 2021-01-27 21:49:44
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-27 22:46:52
 */
#include<bits/stdc++.h>
using namespace std;

stack<int> tower[4];

void moveAndShow(int, int, int, int);

void towerOfHanoi(int n)
{
    for ( int i = n; i > 0; i-- )
        tower[1].push(i);

    moveAndShow(n, 1, 2, 3);
}

void moveAnaShow(int n, int x, int y, int z)
{
    if ( n > 0 ) {
        moveAnaShow(n - 1, x, z, y);
        int d = tower[x].top();
        tower[y].push(d);
        cout << tower->top() << " ";
        moveAndShow(n - 1, z, y, x);
    }
}