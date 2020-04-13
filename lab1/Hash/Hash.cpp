#include <iostream>

#include <map>
#include <vector>

#include "CustomSorts.cpp"
#include "Hash.h"

int hashsearch::FindMax(std::vector<int> values){
	int max = values[0];
	for (auto i: values) {
		if (i > max) {
			max = i;
		}
	}
	return max;
}

int hashsearch::Hash(const int value, const int max) {
	return value % (max / 2);
}


hashsearch::HashTable::HashTable(const std::vector<int> values) {
	max = FindMax(values);
	//Проход массива и применение хеш-функции
	for (auto i: values) {
		int hash = Hash(i,max);
		//Проверка на повтор ключа, есть повтор - добавляем в строку, нет - создать строку
		if (hashTable.count(hash)) {
			hashTable[hash].emplace_back(i);
		}
		else {
			hashTable.emplace(hash, std::vector<int>(1, i));
		}
	}
}
//Построчный вывод хеш-таюлицы
void hashsearch::HashTable::PrintHashTable() {
	std::cout << "Hash table:" << "\n Hash: values\n";
	for (auto i : hashTable) {
		std::cout << i.first << ": ";
		for (auto j : hashTable[i.first]) {
			std::cout << j << ", ";
		}
		std::cout << "\n";
	}
}

//Поиск нужного хеша и проверка, если ли нужное значение в строку, успех - вывод хеша + возврат true
bool hashsearch::HashTable::HashSearh(const int key) {
	int hash = Hash(key, max);
	if (hashTable.count(hash)) {
		for (auto i : hashTable[hash]) {
			if (i == key) {
				std::cout << "The key is in a row with hash = " << i << "\n";
				return true;
			}
			else {
				return false;
			}
		}
	}
}