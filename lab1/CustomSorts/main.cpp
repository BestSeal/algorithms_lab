#include <iostream> 
#include <random>
#include <chrono>
#include "CustomSorts.cpp"

//������� 24, ���������� ������� ����� + ������� 25 ���������� ������� �������

int main()
{
	//������� ��������� ��������� ����� � ����� �������
	const int MIN = 0;
	const int MAX = 100;
	const int SHELL[3] = { 1600, 2800, 8800 };
	const int SELECTION[3] = { 2200,3400,7200 };

	//���������� ����� ������ � ����� ������ ���������
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	std::cout << "Shell sort\n";
	for (auto j : SHELL) {

		//���������� ������� ���������������� �������, ������ ����� ���������� ������� �����
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

	//������ ����� ���������� ������� �������
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