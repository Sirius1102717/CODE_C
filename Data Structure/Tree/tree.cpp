#include<iostream>
#include<new>
#include<algorithm>

typedef struct node
{
    int element;
    struct node *leftChild;
    struct node *rightChild;
}NODE;

void create(NODE **root, int element)
{
    NODE *node = new NODE;
    node->element = element;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    if ( !(*root) )
        *root = node;
    else {
        NODE *p = *root;
        while ( 1 ) {
            if ( element < p->element ) {
                if ( !p->leftChild ) {
                    p->leftChild = node;
                    return;
                } else {
                    p = p->leftChild;
                    // return;
                }
            } else {
                if ( !p->rightChild ) {
                    p->rightChild = node;
                    return;
                } else {
                    p = p->rightChild;
                    // return;
                }
            }
        }
    }
}

void preOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        std::cout << p->element << " ";
        preOrder(p->leftChild);
        preOrder(p->rightChild);
    }
}

void inOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        inOrder(p->leftChild);
        std::cout << p->element << " ";
        inOrder(p->rightChild);
    }
    // printf("\n");
}

void postOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        postOrder(p->leftChild);
        postOrder(p->rightChild);
        std::cout << p->element << " ";
    }
}

//Concise version
int TreeHeight(NODE *root)
{
    NODE *p = root;
    if ( !p )
        return 0;
    else {
        return std::max(TreeHeight(p->leftChild), TreeHeight(p->rightChild)) + 1;
    }
}

//Complex version
int TreeHeight2(NODE *root)
{

    int lHeight = 0;
    int rHeight = 0;
    NODE *p = root;
    if ( !p )
        return 0;
    else {
        lHeight = TreeHeight(p->leftChild);
        rHeight = TreeHeight(p->rightChild);
    }
    if ( lHeight > rHeight )
        return ++lHeight;
    else
        return ++rHeight;

}

int main(int argc, char const *argv[])
{
    NODE *root = nullptr;
    int element;
    int i;
    for ( i = 0; i < 7; i++ ) {
        scanf("%d", &element);
        create(&root, element);
    }
    int height = TreeHeight(root);
    printf("%d", height);
    // preOrder(root);
    // inOrder(root);
    // postOrder(root);
    return 0;
}
