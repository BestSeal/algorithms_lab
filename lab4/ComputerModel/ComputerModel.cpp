#include <iostream>
#include <random>
//Григорьев И.А. ПИН-24 Моделирование ЭВМ
template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
{
    static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

    if (minNum > maxNum) {
        return std::uniform_real_distribution<Type>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с равномерным распределением
    }
    else return std::uniform_real_distribution<Type>(minNum, maxNum)(generator);
}

class Task
{
    int number;
    Task* nextTask;
    

public:
    Task(int num)
    {
        number = num;
        nextTask = nullptr;
    }

    Task* GetNextTask()
    {
        return nextTask;
    }
    void SetNextTask(Task* tmp)
    { 
        nextTask = tmp;
    }
};

class Queue
{
    //размер стека, можно задать в конструкторе или оставить равным максимальному значению int
    int maxSize;
    //текущий размер стека = кол-во элементов в стеке
    int size;
    Task* firstTask;
    Task* lastTask;
    int numOfTasks;

public:
    Queue(int max = INT_MAX) {
        firstTask = nullptr;
        lastTask = nullptr;
        maxSize = max;
        size = 0;
        numOfTasks = 0;
    }

    bool Put()
    {
        if (IsFull())
            return 1;
        ++numOfTasks;
        Task* tmp = lastTask;
        lastTask = new Task(numOfTasks);
        if (size == 0)
        {
            firstTask = lastTask;
        }
        else
            tmp->SetNextTask(lastTask);
        ++size;
        return 0;
    }

    bool Get()
    {
        if (IsEmpty())
            return 1;
        size--;
        firstTask = firstTask->GetNextTask();
        return 0;
    };

    bool IsEmpty()
    {
        if (!size)
            return 1;
        return 0;
    }

    bool IsFull()
    {
        if (size == maxSize)
            return 1;
        return 0;
    }

};

enum struct states
{
    Work,
    Wait
};

class  Computer
{

    states currentState;
    int doneTasks;
    int ignoredTasks;
    int ticks;
public:
    Computer() 
    {
        currentState = states::Work;
        doneTasks = 0;
        ignoredTasks = 0;
        ticks = 0;
    }

    void simulate(int queueSize, int tick, double q1, double q2) 
    {
        Queue thread(queueSize);
        for (int i = 0; i < tick; ++i)
        {
            bool newTask = 0;
            bool work = 0;
            if (RandomNum(0., 1.) < q1)
                newTask = 1;
            if (RandomNum(0., 1.) < q2)
                work = 1;

            switch (currentState)
            {
            case states::Work:
                if (!thread.IsFull() && newTask)
                {
                    thread.Put();
                }
                if (!thread.IsEmpty() && work)
                {
                    thread.Get();
                    ++doneTasks;
                }
                if (!thread.IsFull() && newTask) 
                {
                    ++ignoredTasks;
                }
                break;
            case states::Wait:

                break;
            default:
                break;
            }
        }
    }

    void clear()
    {
        ignoredTasks = 0;
        doneTasks = 0;
    }
    void report()
    {
        std::cout << "Tasks done: " << doneTasks << "\n";
        std::cout << "Tasks ignored: " << ignoredTasks << "\n";
    }
};


int main()
{
    Computer PC;
    PC.simulate(3, 100, 0.5, 0.5);
    PC.report();
    PC.clear();
    PC.simulate(3, 100, 0.5, 0.2);
    PC.report();
    PC.clear();
    PC.simulate(3, 100, 0.2, 0.5);
    PC.report();

}
