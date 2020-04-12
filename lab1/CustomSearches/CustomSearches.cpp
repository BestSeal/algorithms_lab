#include <iostream>
#include <chrono>

//#include "BinTree.h"
#include "CustomSorts.cpp"

int main()
{
    const int LENGTH = 10;
    int values[LENGTH];

    for (auto i = 0; i < LENGTH; ++i) {
        values[i] = customsorts::RandomNum(0, 100);
    }

    customsorts::ShellSort(values, LENGTH);

    for (auto i : values) {
        std::cout << i << " ";
    }
}