#include <iostream> 
#include <random>
#include <chrono>

//Âàðèàíò 24, ñîðòèðîâêà ìåòîäîì Øåëëà + âàðèàíò 25 ñîðòèðîâêà ïðîñòûì âûáîðîì
template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //Ãåíåðàòîð ðàâíîìåðíî ðàñïðåäåëåííûõ ïñåâäîñëó÷àéíûõ ÷èñåë â çàäàííîì äèàïàçîíå.
{
	static std::mt19937 generator(std::random_device{}());//Ñîçäàíèå "çåðíà" è ãåíåðàöèÿ ïñåâäîñëó÷àéíîãî ÷èñëà ñ ïîìîùüþ âèõðÿ Ìåðñåííà

	if (minNum > maxNum) {
		return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //Ïðèâåäåíèå ïñåâäîñëó÷àéíîãî ÷èñëà ê íóæíîìó èíòåðâàëó â ñîîòâåòñòâèè ñ íîðìàëüíûì ðàñïðåäåëåíèåì
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
{	//Ãðàíèöû ãåíåðàöèè ñëó÷àéíûõ ÷èñåë è äëèíà ìàññèâà
	const int MIN = 0;
	const int MAX = 100;
	const int LENGTH = 10000;

	//Îáúÿâëåíèå òî÷åê íà÷àëà è êîíöà ðàáîòû àëãîðèòìà
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	int array[LENGTH];

	//Çàïîëíåíèå ìàññèâà ïñåâäîñëó÷àéíûìè ÷èñëàìè, íà÷àëî òåñòà ñîðòèðîâêè ìåòîäîì Øåëëà
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	ShellSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";

	//íà÷àëî òåñòà ñîðòèðîâêè ïðîñòûì âûáîðîì
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = RandomNum(MIN, MAX);
	}

	startTime = std::chrono::system_clock::now();

	SelectionSort(array, LENGTH);

	endTime = std::chrono::system_clock::now();

	std::cout << "\nDuration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";


}
