#include <iostream> 
#include <random>
#include <chrono>

//������� 24, ���������� ������� ����� + ������� 25 ���������� ������� �������
template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //��������� ���������� �������������� ��������������� ����� � �������� ���������.
{
	static std::mt19937 generator(std::random_device{}());//�������� "�����" � ��������� ���������������� ����� � ������� ����� ��������

	if (minNum > maxNum) {
		return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //���������� ���������������� ����� � ������� ��������� � ������������ � ���������� ��������������
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
{	//������� ��������� ��������� ����� � ����� �������
	const int MIN = 0;
	const int MAX = 100;
	const int LENGTH = 10000;

	//���������� ����� ������ � ����� ������ ���������
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	int array[LENGTH];

	//���������� ������� ���������������� �������, ������ ����� ���������� ������� �����
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	ShellSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";

	//������ ����� ���������� ������� �������
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	SelectionSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";


}