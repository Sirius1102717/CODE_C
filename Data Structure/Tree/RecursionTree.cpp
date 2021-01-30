#include <cstdio>
// #include<iostream>
#include<new>
#include<deque>
#include<exception>

typedef struct node
{
    int element;
    struct node *leftChild, *rightChild;
}NODE;

void preInsert(NODE **root, NODE *node)
{
    if ( !*root )
        *root = node;
    else {
        if ( node->element < (*root)->element )
            preInsert(&((*root)->leftChild), node);
        else
            preInsert(&((*root)->rightChild), node);
    }
}

void create(NODE **root)
{
    int element;
    int i;
    for ( i = 0; i < 7; i++ ) {
        scanf("%d", &element);
        NODE *node = new NODE;
        node->element = element;
        node->leftChild = nullptr;
        node->rightChild = nullptr;
        preInsert(root, node);
    }
}

void visit(NODE *p)
{
    printf("%d ", p->element);
}

void inOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        inOrder(p->leftChild);
        visit(p);
        inOrder(p->rightChild);
    }
}


void levelOrder(NODE *root)
{
    std::deque<NODE *> q;
    q.push_back(root);
    while ( !q.empty() ) {
        NODE *p = nullptr;
        p = q.front();
        visit(p);
        if ( p->leftChild )
            q.push_back(p->leftChild);
        if ( p->rightChild )
            q.push_back(p->rightChild);
        q.pop_front();
    }

}

int main(int argc, char const *argv[])
{
    NODE *root = nullptr;
    create(&root);
    // inOrder(root);
    levelOrder(root);
    return 0;
}


