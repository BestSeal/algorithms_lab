#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <random>
//Григорьев И.А. ПИН-24, маршрутный алгоритм
template<typename Type>
Type RandomNum(const Type minNum, const Type maxNum) //Генератор равномерно распределенных псевдослучайных чисел в заданном диапазоне.
{
    static std::mt19937 generator(std::random_device{}());//Создание "зерна" и генерация псевдослучайного числа с помощью вихря Мерсенна

    if (minNum > maxNum) {
        return std::uniform_int_distribution<Type>(maxNum, minNum)(generator); //Приведение псевдослучайного числа к нужному интервалу в соответствии с равномерным распределением
    }
    else return std::uniform_int_distribution<Type>(minNum, maxNum)(generator);

}
enum struct fieldType 
{
    Finish,
    Start,
    Wall,
    Path,
    StepHere
};

//Координаты
struct  XY
{
    int x;
    int y;
    XY(int xx = 0, int yy = 0)
    {
        x =xx;
        y = yy;
    }

};
//Поле для лабитрилабиринтарнта
struct Field
{
    int x, y;
    double value;
    fieldType status;

    Field(int inX, int inY, int inValue = 0, fieldType newField = fieldType::Path)
    {
        x = inX;
        y = inY;
        value = inValue;
        status = newField;
    }

};

class Labirint
{
    std::vector<std::vector<Field*>> labirint;
    Field* finish;
    Field* start;
    XY coords;
    int len;

public:
    Labirint (int n)
    {
        len = n;
        for (int i = 0; i < n; ++i)
        {
            labirint.push_back(std::vector<Field*>());
            for (int j = 0; j < n; ++j)
                labirint[i].push_back(new Field(j, i));
        }
    }
    //инициализация начала и конца
    void SetStartFinish(int xs, int ys, int xf, int yf) 
    {
        labirint[yf][xf]->status = fieldType::Finish;
        labirint[yf][xf]->value = DBL_MAX;
        finish = labirint[yf][xf];
        labirint[ys][xs]->status = fieldType::Start;
        labirint[ys][xs]->value = DBL_MAX;
        start = labirint[ys][xs];
        coords.x = xs;
        coords.y = ys;
    }
    //добавление стены
    bool AddWall(int xw,int yw)
    {
        if (!((start->x == xw && start->y == yw) || (finish->x == xw && finish->y == yw)))
        {
            labirint[yw][xw]->status = fieldType::Wall;
            labirint[yw][xw]->value = DBL_MAX;
            return 1;
        }
        return 0;
    }

    //Отрисовка лабиринта
    void Show()
    {
        for (auto i : labirint)
        {
            for (auto j : i)
            {
                switch (j->status)
                {
                case fieldType::Path:
                    //if (j->value == 0)
                        std::cout << "_";
                    ///else
                    //std::cout << j->value;
                    break;
                case fieldType::Wall:
                    std::cout << "*";
                    break;
                case fieldType::Finish:
                    std::cout << "F";
                    break;
                case fieldType::Start:
                    std::cout << "S";
                    break;
                case fieldType::StepHere:
                    std::cout << "^";
                default:
                    break;
                }
            }
            std::cout << "\n";
        }
    }

    //проверка поля + вычисление d
    fieldType  Check(int dx, int dy, bool& valid) 
    {
        if (coords.y  + dy >= 0 && coords.y + dy <= len - 1 && coords.x + dx >= 0 && coords.x + dx <= len - 1)
            switch (labirint[coords.y + dy][coords.x + dx]->status)
            {
            case fieldType::Path:
                labirint[coords.y + dy][coords.x + dx]->value = std::hypot(coords.y + dy - finish->y, coords.x + dx - finish->x);
                valid = 1;
                return fieldType::Path;
                break;
            case fieldType::Finish:
                coords.x += dx;
                coords.y += dy;
                valid = 1;
                return fieldType::Finish;
            case fieldType::Wall:
                valid = 1;
                return fieldType::Wall;
            case fieldType::Start:
                valid = 1;
                return fieldType::Start;
            case fieldType::StepHere:
                valid = 1;
                return fieldType::StepHere;
            default:
                break;
            }
        valid = 0;
    }

    bool Pulse()
    {
        //Выпуск волны и посик пути + отслеживание финиша и пометка пути
        std::vector<XY> sides = {XY(1,1), XY(1,-1), XY(-1,-1), XY(-1,1), XY(-1,1), XY(0,1), XY(1,0), XY(-1,0), XY(0,-1)};
        XY newCoords;
        double min = DBL_MAX;
        for (auto i : sides)
        {
            bool valid;
            if (Check(i.x, i.y, valid) == fieldType::Finish)
                return 1;
            if (!valid)
                continue;
            if (labirint[coords.y + i.y][coords.x + i.x]->value < min && labirint[coords.y + i.y][coords.x + i.x]->status == fieldType::Path)
            {
                min = labirint[coords.y + i.y][coords.x + i.x]->value;
                newCoords.x = coords.x + i.x;
                newCoords.y = coords.y + i.y;
            }
        }
        coords = newCoords;
        labirint[coords.y][coords.x]->status = fieldType::StepHere;
        return 0;
    }

};


int main()
{
    int n = 30;
    int xf = RandomNum(0,n/2), yf = RandomNum(0, n/2), xs = RandomNum(n/2, n-1), ys = RandomNum(n/2, n-1);

    Labirint test(n);
    test.SetStartFinish(xs, ys, xf, xf);
    std::cout.precision(1);
    for (int i = 0; i < 400; ++i) 
    {
        test.AddWall(RandomNum(0,n-1), RandomNum(0,n-1));
    }

    while (!test.Pulse());
    test.Show();



    

    
        
}
