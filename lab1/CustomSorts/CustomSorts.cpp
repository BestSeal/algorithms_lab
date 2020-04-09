#include <iostream> 
#include <random>
#include <chrono>

//Вариант 24, сортировка методом Шелла + вариант 25 сортировка простым выбором
template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
{
	static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

	if (minNum > maxNum) {
		return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с нормальным распределением
	}
	else return std::uniform_int_distribution<Type>(minNum, maxNum)(generator); 

}

//Метод Шелла
template<typename ArrType, typename LenType>
void ShellSort(ArrType* array, const LenType length) {

	//Сравнение элементов на дистанции шага step, при step = 1 вырождается в сортировку вставками
	for (auto step = length / 2; step > 0; step /= 2)
		for (auto i = step; i < length; ++i)
			for (auto j = i - step; j >= 0 && array[j] > array[j + step]; j -= step) 
				std::swap(array[j], array[j + step]);
}

//Сортировка выбором
template<typename ArrType, typename LenType>
void SelectionSort(ArrType* array, const LenType length) {
	ArrType min, ind;

	//Перебор элементов от 0 до length
	for (auto i = 0; i < length; ++i) { 
		min = array[i];
		ind = i;

		//Поиск минимума от i до length и его размещение на i-ом месте
		for (auto j = i; j < length; ++j) {
			if (min > array[j]) {
				min = array[j];
				ind = j;
			}
		}
		std::swap(array[i], array[ind]);
	}
}

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
			array[i] = RandomNum(MIN, MAX);
		}

		startTime = std::chrono::system_clock::now();

		ShellSort(array, j);

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
			array[i] = RandomNum(MIN, MAX);
		}

		startTime = std::chrono::system_clock::now();

		SelectionSort(array, j);

		endTime = std::chrono::system_clock::now();
		delete[] array;
		std::cout << " Number of elemments:" << j << " Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";
	}
}