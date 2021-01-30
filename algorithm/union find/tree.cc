/*
 * @Author: Freaver
 * @Date: 2021-01-26 19:24:45
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-26 21:17:49
 */


#include<bits/stdc++.h>
using namespace std;

typedef struct unionFindNode
{
    int parent;
    bool root;

    unionFindNode()
    {
        parent = 1;
        root = true;
    }
}UFN;

void pathCompaction(UFN *node, int currentNode, int theRoot)
{
    while ( currentNode != theRoot ) {
        node[currentNode].parent = theRoot;
        currentNode = node[currentNode].parent;
    }
}

void pathSplitting(UFN *node, int currentNode, int theRoot)
{
    while(currentNode != theRoot) {
        node[currentNode].parent = node[node[currentNode].parent].parent;
        currentNode = node[currentNode].parent;
    }
}

void pathHalving(UFN *node, int currentNode, int theRoot)
{
    while ( currentNode != theRoot ) {
        node[currentNode].parent = node[node[currentNode].parent].parent;
        currentNode = node[node[currentNode].parent].parent;
    }
}

int getParent(int theElement, UFN *node)
{
    int theRoot = theElement;
    int currentNode = theElement;
    while ( !node[theRoot].root ) {
        theRoot = node[theRoot].parent;
    }

    return theRoot;
}

void f(UFN *node, int rootA, int rootB)
{
    node[rootA].parent = rootB;
    node[rootA].root = false;
}

void unite(UFN *node, int rootA, int rootB)
{
    if ( node[rootA].parent < node[rootB].parent )
        f(node, rootA, rootB);
    else if ( node[rootA].parent > node[rootB].parent )
        f(node, rootB, rootA);
    else {
        f(node, rootB, rootA);
        node[rootA].parent++;
    }
}

void fmerge(UFN *node, int xi, int yi)
{

    int t1 = getParent(xi, node);
    int t2 = getParent(yi, node);
    if ( t1 != t2 )
        unite(node, t1, t2);
}

int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;
    UFN node[n + 1];
    int xi, yi;
    int i;
    for ( i = 0; i < m; i++ ) {
        cin >> xi >> yi;
        fmerge(node, xi, yi);
    }

    for ( i = 0; i < k; i++ ) {
        cin >> xi >> yi;
        if ( getParent(xi, node) == getParent(yi, node) )
            cout << "yes" << "\n";
        else
            cout << "no" << "\n";
    }
    return 0;
}
