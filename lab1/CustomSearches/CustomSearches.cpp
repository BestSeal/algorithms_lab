#include <iostream>
#include <chrono>

#include "BinTree.h"
//#include "SearchByHash.cpp"
#include "CustomSorts.cpp"

int main()
{   
    //Бинарное дерево поиска
    //Пример отсортированном массиве 
    const int LENGTH = 10;
    int values[LENGTH];

    for (auto i = 0; i < LENGTH; ++i) {
        values[i] = customsorts::RandomNum(0, 100);
    }

    customsorts::ShellSort(values, LENGTH);

    bintree::BinTree* sortedInput = new bintree::BinTree(values, LENGTH, true);
    //Должен быть отсортирован
    sortedInput->InorderTreePrint(sortedInput->GetRoot());
    std::cout << "\n";
    sortedInput->PreorderTreePrint(sortedInput->GetRoot());
    std::cout << "\n";

    for (auto i : values) {
        std::cout << "Is tree containing " << i << "?  " << sortedInput->IsContaining(i) << "\n";
    };
    //Удаление элемента 
    sortedInput->DeleteElement(values[6]);

    std::cout << "Is tree containing " << values[6] << "?  " << sortedInput->IsContaining(values[6]) << "\n";
    sortedInput->InorderTreePrint(sortedInput->GetRoot());
    std::cout << "\n";
    sortedInput->DeleteElement(values[0]);
    std::cout << "Is tree containing " << values[0] << "?  " << sortedInput->IsContaining(values[0]) << "\n";
    sortedInput->InorderTreePrint(sortedInput->GetRoot());
    std::cout << "\n";
    delete sortedInput;

    std::cout << "\n";
    //Пример с последовательностью в preorder-виде
    int values1[]{8,2,1,4,3,5};

    bintree::BinTree* preorderInput = new bintree::BinTree(values1, 6, false);
    //Должен быть отсортирован
    preorderInput->InorderTreePrint(preorderInput->GetRoot());
    std::cout << "\n";
    //Должен совпасть с входной
    preorderInput->PreorderTreePrint(preorderInput->GetRoot());
    std::cout << "\n";

    std::cout << "Is tree containing " << 2 << "?  " << preorderInput->IsContaining(2) << "\n";
    preorderInput->InorderTreePrint(preorderInput->GetRoot());
    std::cout << "\n";

}