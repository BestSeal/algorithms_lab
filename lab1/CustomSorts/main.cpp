#include <iostream> 
#include <random>
#include <chrono>
#include "CustomSorts.cpp"

//Вариант 24, сортировка методом Шелла + вариант 25 сортировка простым выбором 

int main()
{
	//Границы генерации случайных чисел и длина массива
	const int MIN = 0;
	const int MAX = 100;
	const int SHELL[3] = { 1600, 2800, 8800 };
	const int SELECTION[3] = { 2200,3400,7200 };

	//Объявление точек начала и конца работы алгоритма
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	std::cout << "Shell sort\n";
	for (auto j : SHELL) {

		//Заполнение массива псевдослучайными числами, начало теста сортировки методом Шелла
		int* array = new int[j];
		for (int i = 0; i < j; ++i)
		{
			array[i] = customsorts::RandomNum(MIN, MAX);
		}

		startTime = std::chrono::system_clock::now();

		customsorts::ShellSort(array, j);

		endTime = std::chrono::system_clock::now();
		delete[] array;
		std::cout << " Number of elemments:" << j << " Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";
	}

	//начало теста сортировки простым выбором
	std::cout << "\nSelection sort\n";
	for (auto j : SELECTION) {
		int* array = new int[j];
		for (int i = 0; i < j; ++i)
		{
			array[i] = customsorts::RandomNum(MIN, MAX);
		}

		startTime = std::chrono::system_clock::now();

		customsorts::SelectionSort(array, j);

		endTime = std::chrono::system_clock::now();
		delete[] array;
		std::cout << " Number of elemments:" << j << " Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";
	}
}