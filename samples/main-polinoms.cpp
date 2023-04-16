#include "../include/M_List.h"

enum CHOISE { ex,add, sub, mult1,mult2, };

void contSwitch(bool& cont)
{
    std::string s;
    for (;;) {
        std::cout << "Continue input? y/n" << std::endl;
        std::cin >> s;
        if (s == "y" || s == "yes")
        {
            cont = true;
            return;
        }
        if (s == "n" || s == "no")
        {
            cont = false;
            return;
        }
    }
};
void ignoreLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Input error." << std::endl;;
};

void set(polinom& p)
{
    int tmp;
    bool cont = true;
    while (cont) {
        double a = 0;
        int xyz = 0;
        std::cout << "Enter the polinomial degree."
            << std::endl << "x: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            contSwitch(cont);
            continue;
        }
        xyz += tmp * 100;

        std::cout << "y: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            contSwitch(cont);
            continue;
        }

        xyz += tmp * 10;

        std::cout << "z: ";
        std::cin >> tmp;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            ignoreLine();
            contSwitch(cont);
            continue;
        }

        xyz += tmp;

        std::cout <<"Coef: ";
        std::cin >> a;

        if (std::cin.fail())
        {
            ignoreLine();
            contSwitch(cont);
            continue;
        }

        p.push(monom{a,xyz});
        contSwitch(cont);
    }
    p.butifie();
    p.show();
    std::cout << std::endl;
    system("PAUSE");
}

int main()
{
	polinom p;
    std::cout << "Use '.' as decimal separator.Simular terms are reduce." << std::endl;
    set(p);
    for (;;) 
    {
        polinom p2;
        double m = 1;
        
        CHOISE ch = ex;
        std::cout << "1.add" <<
        std::endl << "2.sub" <<
        std::endl << "3.polinomial mult" <<
        std::endl << "4.mult by const" <<
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
        case mult1:           
            set(p2);
            try { p = p * p2; }
            catch (const std::domain_error& e) { std::cerr << e.what(); exit(-1); }
            break;
        case mult2:
            for (;;) {
                std::cout << "Enter the constant:";
                std::cin >> m;
                if (std::cin.fail())
                {
                    ignoreLine();
                    continue;
                }
                break;
            }
            p = p * m;
            break;
        case ex:
            exit(0);
            break;
        default:
            std::cout << "Incorrect input" << std::endl;
            break;
        }
        std::cout << "Result:" << std::endl;
        p.show();
    system("PAUSE");
    }
}