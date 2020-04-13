#pragma once

namespace hashsearch {

	//Поиск максимума
	int FindMax(std::vector<int> values);
	//Вычисление хеш-функции
	int Hash(const int value, const int max);

	class HashTable {

		//Хеш-таблица
		std::map <int, std::vector<int>> hashTable;
		int max;

	public:

		HashTable(const std::vector<int> values);
		//Вывод хеш-таблицы
		void PrintHashTable();
		//Поиск в хеш-таблице, результат - значение хеша (строка) и true, если значение найдено и false иначе
		bool HashSearh(const int key);
	};
}
