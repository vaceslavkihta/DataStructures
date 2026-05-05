#include <iostream>
#include "RBT.h"

using namespace DataStructures;

int main()
{
    rbt<int> myTree;
    for (int i = 1; i <= 8; ++i) {
        myTree.insert(i);
    }
    myTree.print();
}