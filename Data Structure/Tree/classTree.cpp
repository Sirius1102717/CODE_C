#include<stdio.h>
#include<new>
#include<deque>
using namespace std;

typedef class Tree
{
    int element;
    class Tree *leftChild, *rightChild;
    void visit()
    {
        printf("%d ", this->element);
    }
public:
    static void create(class Tree **root, int element);
    void preOrder(class Tree *root);
    void inOrder(class Tree *root);
    void postOrder(class Tree *root);
    void levelOrder(class Tree *root);
    void preInsert(class Tree **root, class Tree *node);
    int TreeHeight(class Tree *root);

    
}NODE;

void NODE::create(class Tree **root, int element)
{
    int i;
    NODE *node = new NODE;
    node->element = element;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    (*root)->preInsert(root, node);

}

void Tree::preOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        p->visit();
        preOrder(p->leftChild);
        preOrder(p->rightChild);
    }
}

void Tree::inOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        inOrder(p->leftChild);
        p->visit();
        inOrder(p->rightChild);

    }
}

void Tree::postOrder(NODE *root)
{
    NODE *p = root;
    if ( p ) {
        postOrder(p->leftChild);
        postOrder(p->rightChild);
        p->visit();
    }
}

void Tree::levelOrder(NODE *root)
{
    deque<NODE *> q;
    q.push_back(root);
    while ( !q.empty() ) {
        NODE *p = nullptr;
        p = q.front();
        p->visit();
        if ( p->leftChild )
            q.push_back(p->leftChild);
        if ( p->rightChild )
            q.push_back(p->rightChild);
        q.pop_front();
    }

}

void Tree::preInsert(class Tree **root, class Tree *node)
{
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
}

int Tree::TreeHeight(NODE *root)
{
    NODE *p = root;
    if ( !p )
        return 0;
    else {
        return std::max(TreeHeight(p->leftChild), TreeHeight(p->rightChild)) + 1;
    }
}

int main(int argc, char const *argv[])
{
    NODE *root = nullptr;
    int element;
    int i;
    for ( i = 0; i < 7; i++ ) {
        scanf("%d", &element);
        Tree::create(&root, element);
    }
    int height = root->TreeHeight(root);
    printf("%d\n", height);
    root->preOrder(root);
    printf("\n");
    root->postOrder(root);
    printf("\n");
    root->inOrder(root);
    printf("\n");
    root->levelOrder(root);
    return 0;
}

