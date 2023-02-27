#include "../src/M_List.cpp"

enum CHOISE { add, sub, mult, ex };

void set(polinom& p)
{
    int tmp;
    for (;;) {
        double a = 0;
        int xyz = 0;
        std::cout << "Enter the polinomial degree. To complete the input enter a degree greater than 9 or not a number."
            << std::endl << "x: ";
        std::cin >> tmp;
        std::cout << std::endl;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            std::cin.clear();
            std::cout << "Enter is over." << std::endl;
            return;
        }
        xyz += tmp * 100;

        std::cout << "y: ";
        std::cin >> tmp;
        std::cout << std::endl;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            std::cin.clear();
            std::cout << "Enter is over." << std::endl;
            return;
        }

        xyz += tmp * 10;

        std::cout << "z: ";
        std::cin >> tmp;
        std::cout << std::endl;

        if (std::cin.fail() || tmp > 9 || tmp < 0)
        {
            std::cin.clear();
            std::cout << "Enter is over." << std::endl;
            return;
        }

        xyz += tmp;

        std::cout << std::endl << "Coef: ";
        std::cin >> a;
        std::cout << std::endl;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Enter is over." << std::endl;
            return;
        }


        p.push(a, xyz);
    }
}

int main()
{
	polinom p;
    std::cout << "Enter first polinomial"<< std::endl;
    set(p);
    for (;;) 
    {
        polinom p2;
        system("CLS");
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