#include<linkBinayTree.h>
#include<iostream>
using namespace std;

struct booster
{
    int degradeToLeaf;
    int degradeFromParent;
    bool boosterHere;

    void output(ostream &out) const
    {
        out << boosterHere << " " << degradeToLeaf << " "
            << degradeFromParent << " ";
    }
};

ostream &operator<<(ostream &out, booster x)
{
    x.output(out);
    return out;
}

void placeBoosters(binaryTreeNode<booster> *x, int tolerance)
{
    x->element.degradeToLeaf = 0;

    binaryTreeNode<booster> *y = x->leftChild;
    if(y) {
        int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
        if (degradation > tolerance) {
            y->element.boosterHere = true;
            x->element.degradeToLeaf = y->element.degradeFromParent;
        } else {
            x->element.degradeToLeaf = degradation;
        }

        y = x->rightChild;
        if (y) {
            int degradation = y->element.degradeToLeaf + y->element.degradeFromParent;
            if (degradation > tolerance) {
                y->element.boosterHere = true;
                degradation = y->element.degradeFromParent;
            }
            if (x->element.degradeToLeaf < degradation)
                x->element.degradeToLeaf = degradation;
        }
    }
}

int main(int argc, char const *argv[])
{
    return 0;
}

