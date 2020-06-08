#include <iostream>
//Григорьев И.А. Пин-24, вариант 24. Выражение an = 2^n(n-1)!

//при значении большем unt64_t будет ошибка. С беззнаковым типом произойдёт зацикливание, по этому оставлена знаковость.
std::int64_t Power(int num, int power)
{
    if (power > 0)
    {
        return Power(num, power - 1) * num;
    }
    else
        return 1;

}

std::int64_t Fact(int num)
{
    if (num > 0)
    {
        return Fact(num - 1) * num;
    }
    else
        return 1;
}

int main()
{
    std::int32_t n;
    std::cout << "Please, enter n for evaluetion 2^n*(n-1)!\n";
    std::cin >> n;
    std::cout << "2^" << n << "*(" << n << "-1)! = " << Power(2, n) * Fact(n-1);
}
