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

template<typename ArrType, typename LenType>
void ShellSort(ArrType* array, const LenType length) {
	LenType j = 0;
	bool ayversonCond;
	for (auto step = length / 2; step > 1; step /= 2)
		for (auto i = 0; i + step < length; ++i)
			if (array[i] > array[i + step]) {
				std::swap(array[i], array[i + step]);
			}

	for (auto j = 0; j < length; ++j) {
		ayversonCond = false;
		for (auto i = 0; i < length - j - 1; ++i) {
			if (array[i] > array[i + 1]) {
				ayversonCond = true;
				std::swap(array[i], array[i + 1]);
			}

		}
		if (!ayversonCond) break;
	}
}

template<typename ArrType, typename LenType>
void SelectionSort(ArrType* array, const LenType length) {
	ArrType min, ind;
	for (auto i = 0; i < length; ++i) {
		min = array[i];
		ind = i;
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
{	//Границы генерации случайных чисел и длина массива
	const int MIN = 0;
	const int MAX = 100;
	const int LENGTH = 10000;

	//Объявление точек начала и конца работы алгоритма
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	int array[LENGTH];

	//Заполнение массива псевдослучайными числами, начало теста сортировки методом Шелла
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	ShellSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";

	//начало теста сортировки простым выбором
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	SelectionSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";


}