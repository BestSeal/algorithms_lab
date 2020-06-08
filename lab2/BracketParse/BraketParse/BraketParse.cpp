#include <iostream>
#include <string>
#include <vector>
//Григорьев И.А., ПИН-24 программа проверки правильности ввода арифм-го выражения
//класс "ячейки" стека
class block 
{   
    //поле для хранения символа
    char sym; 
    //ссылка на предыдущий блок
    block* prevBlock; 

public:
    block(const char inSym, block* block)
    {
        sym = inSym;
        prevBlock = block;

    }

    //получения символа
    char getSym() 
    {
        return sym;
    }

    //получение ссылки на предыдущий блок
    block* getPrevBlock() 
    {
        return prevBlock;
    }
};

//класс стек
class stack 
{
    //размер стека, можно задать в конструкторе или оставить равным максимальному значению int
    int maxSize; 
    //текущий размер стека = кол-во элементов в стеке
    int size; 
    block* topBlock;

public:
    stack(int max = INT_MAX) {
        topBlock = new block(' ', nullptr);
        maxSize = max;
        size = 0;
    }

    //добавление элемента в стек, если превышен размер int, вернёт 1
    bool Push(const char sym) 
    {
        if (size == maxSize)
        {
            return 1;
        }
        ++size;
        topBlock = new block(sym, topBlock);
        return 0;

    }

    //снятие верхнего элемента из стека
    bool Pop(char* sym) 
        
    {
        if (topBlock->getPrevBlock() == nullptr) 
        {
            return 1;
        }
        --size;
        block* temp = topBlock->getPrevBlock();
        *sym = topBlock->getSym();
        delete topBlock;
        topBlock = temp;
        return 0;
    };

};


int main()
{
    std::cout << "Hi! Please, enter your expression and i'll check it's correctness!\nDon't use spaces between symbols!\n";
    std::string expression;
    std::cin >> expression;

    // объявления и инициализация списков букв, цифр и поддерживаемых операторов для идентификации
    std::string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    std::string nums = "1234567890";
    std::string operators = "+-*/!^()";

    // стек для обработки скобок
    stack Brackets;
    //перечисления видов символов
    enum struct SymbolType
    {
        Number,
        Letter,
        PlusMinus,
        Power,
        Fact,
        BracketOpen,
        BracketClose,
        Multipl,
        Div,
        FirstSymbol,
    };

    //инициализация начального состояния проверки
    SymbolType state = SymbolType::FirstSymbol;
    SymbolType prevState = SymbolType::FirstSymbol;
    std::uint64_t position = 1;

    for (auto i : expression)
    {
        prevState = state;
        //Проверка на принадлежность конкретной группе символов, если не найден ни в одной группе - ошибка и выход из программы
        std::size_t symbol = alphabet.find(i);
        if (symbol != std::string::npos) 
        {
           // std::cout << "letter - '" << i << "'\n";
            state = SymbolType::Letter;
        }
        else 
        {
            std::size_t symbol = nums.find(i);
            if (symbol != std::string::npos)
            {
                //std::cout << "number - '" << i << "'\n";
                state = SymbolType::Number;
            }
            else
            {
                std::size_t symbol = operators.find(i);
                if (symbol != std::string::npos)
                {
                    //определение оператора и проверка скобок
                    //std::cout << "operator - '" << i << "'\n";
                    switch (i)
                    {
                    case '+':
                    case '-':
                        state = SymbolType::PlusMinus;
                        break;
                    case '^':
                        state = SymbolType::Power;
                        break;
                    case '!':
                        state = SymbolType::Fact;
                        break;
                    case '*':
                        state = SymbolType::Multipl;
                        break;
                    case '/':
                        state = SymbolType::Div;
                        break;
                    case '(':
                        state = SymbolType::BracketOpen;
                        if (Brackets.Push('('))
                        {
                            //std::cout << "Brackets parse error with (\n";
                            return 1;
                        }
                        break;
                    case ')':
                        state = SymbolType::BracketClose;
                        char tempSym;
                        if (Brackets.Pop(&tempSym))
                        {
                            //std::cout << "Brackets parse error with )\n";
                            return 1;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    std::cout << "An undefiend symbol accured - " << i << " at the position " << position << "\n";
                    return 1;
                }
            }
        }

        switch (state)
        {
        case SymbolType::Number:
            if (prevState == SymbolType::Fact || prevState == SymbolType::Letter || prevState == SymbolType::BracketClose)
            {
                std::cout << "Number parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::Letter:
            if (prevState == SymbolType::Fact || prevState == SymbolType::BracketClose)
            {
                std::cout << "Letter parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::PlusMinus:
            break;
        case SymbolType::Power:
            if (!(prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::BracketClose))
            {
                std::cout << "Power parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::Fact:
            if (!(prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::BracketClose))
            {
                std::cout << "Factorial parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::BracketOpen:
            if (prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::BracketClose)
            {
                std::cout << "Closing bracket parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::BracketClose:
            if (!(prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::Fact))
            {
                std::cout << "Closing bracket parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::Multipl:
            if (!(prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::Fact || prevState == SymbolType::BracketClose))
            {
                std::cout << "Closing bracket parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        case SymbolType::Div:
            if (!(prevState == SymbolType::Number || prevState == SymbolType::Letter || prevState == SymbolType::Fact || prevState == SymbolType::BracketClose))
            {
                std::cout << "Closing bracket parse error with symbol " << i << " at the position " << position << "\n";
                return 1;
            }
            break;
        default:
            break;
        }
        ++position;
    }
    char tempSym;
    if (!Brackets.Pop(&tempSym))
    {
        std::cout << "Unclosed bracket detected!\n";
        return 1;
    }
    std::cout << "Everything is ok :D\n";

    return 0;
}

