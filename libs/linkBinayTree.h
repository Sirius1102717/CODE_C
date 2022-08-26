template<class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    binaryTreeNode()
    {
        leftChild = rightChild = nullptr;
    }

    binaryTreeNode(const T &theElement)
    {
        element(theElement);
        leftChild = rightChild = nullptr;
    }

    binaryTreeNode(const T &theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild)
    {
        element(&element);
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template<class T>
class binaryTree
{
public:
    virtual ~binaryTree() { };
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*) (T *)) = 0;
    virtual void inOrder(void (*) (T *)) = 0;
    virtual void postOrder(void (*) (T *)) = 0;
    virtual void levelOrder(void (*) (T *)) = 0;
};

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
private:
    binaryTreeNode<E> *root;
    int treeSize;
    static void (*visit) (binaryTreeNode<E> *);
    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void dispose(binaryTreeNode<E> *t)
    {
        delete t;
    }
public:
    linkedBinaryTree()
    {
        root = nullptr;
        treeSize = 0;
    }

    ~linkedBinaryTree()
    {
        erase();
    };

    bool empty() const
    {
        return treeSize == 0;
    }

    int size() const
    {
        return treeSize;
    }

    void preOreder(void(*theVisit) (binaryTreeNode<E> *))
    {
        visit = theVisit;
        preOrder(root);
    }
    void inOreder(void(*theVisit) (binaryTreeNode<E> *))
    {
        visit = theVisit;
        inOrder(root);
    }
    void postOreder(void(*theVisit) (binaryTreeNode<E> *))
    {
        visit = theVisit;
        postOrder(root);
    }

    void levelOrder(void(*) (binaryTreeNode<E> *));

    void erase()
    {
        postOrder(dispose);
        root = nullptr;
        treeSize = 0;
    }
};

