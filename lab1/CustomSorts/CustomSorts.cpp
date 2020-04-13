#include <iostream> 
#include <random>
namespace customsorts {

	template<typename Type>
	Type RandomNum(const Type minNum, const Type maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
	{
		static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

		if (minNum > maxNum) {
			return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с равномерным распределением
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
}