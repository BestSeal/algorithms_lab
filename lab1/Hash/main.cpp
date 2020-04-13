#include <iostream>

#include <map>
#include <vector>

#include "CustomSorts.cpp"
#include "Hash.h";
int main()
{
	const int LENGTH = 20;
	std::vector <int> values;
	std::cout << "Input values:";
	for (int i = 0; i < LENGTH; ++i) {
		values.push_back(customsorts::RandomNum(0, 100));
		std::cout << values[i] << " ";
	}
	std::cout << "\n";

	hashsearch::HashTable table(values);
	table.PrintHashTable();
	std::cout << table.HashSearh(values[1]);
}
