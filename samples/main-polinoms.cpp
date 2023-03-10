#include "../include/M_List.h"

enum CHOISE { ex,add, sub, mult };

void ignoreLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter is over." << std::endl;
}

void set(polinom& p)
{
    int tmp;
    for (;;) {
        double a = 0;
        int xyz = 0;
        std::cout << "Enter the polinomial degree. To complete the input enter a degree greater than 9 or not a number."
            << std::endl << "x: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            break;
        }
        xyz += tmp * 100;

        std::cout << "y: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            break;
        }

        xyz += tmp * 10;

        std::cout << "z: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            break;
        }

        xyz += tmp;

        std::cout <<"Coef: ";
        std::cin >> a;

        if (std::cin.fail())
        {
            ignoreLine();
            break;
        }

        p.push(a, xyz);
    }
    system("CLS");
    std::cout << p;
    system("PAUSE");
}

int main()
{
    system("chcp 1251");
	polinom p;
    std::cout << "Enter first polinomial"<< std::endl;
    set(p);
    for (;;) 
    {
        polinom p2;

        CHOISE ch = ex;
        std::cout << "1.add" <<
        std::endl << "2.sub" <<
        std::endl << "3.mult" <<
        std::endl << "0.exit" << std::endl;
        scanf_s("%d", &ch);
        switch (ch)
        {
        case add:
            set(p2);
            p = p + p2;
            break;
        case sub:
            set(p2);
            p = p - p2;
            break;
        case mult:
            set(p2);
            p = p * p2;
            break;
        case ex:
            system("CLS");
            std::cout << p;
            exit(0);
            break;
        default:
            std::cout << "Incorrect input" << std::endl;
            break;
        }

	std::cout << p;
    system("PAUSE");
    }
}