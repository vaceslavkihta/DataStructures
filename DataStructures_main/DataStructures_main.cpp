#include <iostream>
#include "RBT.h"

using namespace DataStructures;

template<typename KeyT>
using node = DataStructures::Node<KeyT>;

using col = DataStructures::Colours;

int main()
{
    node<int>* a = new Node<int>{ 2, nullptr, nullptr, nullptr, col::red },
        *b = new Node<int>{ 1, nullptr, nullptr, nullptr, col::black };

    DataStructures::reverseColour(a, b);
    cout << a->colour << '\t' << b->colour;
}

