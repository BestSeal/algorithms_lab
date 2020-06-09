#include <iostream>
#include <vector>
#include <random>
#include <chrono>

template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
{
    static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

    if (minNum > maxNum) {
        return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с равномерным распределением
    }
    else return std::uniform_int_distribution<Type>(minNum, maxNum)(generator);
}

struct Part
{
    int Ta;
    int Tb;
    int Tc;
    Part(int a = RandomNum(1,100), int b = RandomNum(1,100), int c = RandomNum(1,100)) 
    {
        Ta = a;
        Tb = b;
        Tc = c;
    }
};


int InTheFace(int N, std::vector<Part*>* parts)
{
    unsigned int time = 0;
    for (auto i : *parts)
    {
        time += i->Ta + i->Tb + i->Tc;
    }
    return time;
}


int main()
{
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    int N = 10000;
    std::vector<Part*> parts;

    for (int i = 0; i < N; ++i)
    {
        parts.push_back(new Part());
    }


    startTime = std::chrono::system_clock::now();
    std::cout << InTheFace(N, &parts) << " \n";
    endTime = std::chrono::system_clock::now();
    std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms \n";

}
