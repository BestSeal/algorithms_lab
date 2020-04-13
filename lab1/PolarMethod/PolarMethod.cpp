#include <iostream>
#include <random>
#include <cmath>
double UniformRealDist(const int minNum, const int maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
{
	static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

	if (minNum > maxNum) {
		return std::uniform_real_distribution<double>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с равномерным распределением
	}
	else return std::uniform_real_distribution<double>(minNum, maxNum)(generator);

}
int main()
{	
	double s = 1 , u1, u2, v1, v2;
	//Генерация двух случайных независимых вещественных числа
	while (s >= 1) {
		u1 = UniformRealDist(0, 1);
		u2 = UniformRealDist(0, 1);
		v1 = u1 * 2 - 1;
		v2 = u2 * 2 - 1;
		s = pow(v1, 2) + pow(v2, 2);
	}
	std::cout << "n1 = " << v1 * sqrt(-2 * log(s) / s) << ", n2 = " << v2 * sqrt(-2 * log(s) / s) << "\n";
		
}
