#include <iostream>
#include <chrono>

#include "CustomSorts.cpp"
#include "BinTree.h"

int main()
{
    const int LENGTH = 10;
    int values[LENGTH];

    for (auto i = 0; i < LENGTH; ++i) {
        values[i] = customsorts::RandomNum(0, 100);
    }

    bintree::BinTree(values, LENGTH);

    for (auto i : values) {
        std::cout << i << " ";
    }

    
}