#pragma once
#include <iostream>
/* Структура monom обеспечивает хранение коэффицента монома, показатель степени
* переменных в виде десятичного разложения целого числа в виде 100*log_x(X)+10*
* *10*log_y(Y)+log_z(Z). X,Y,Z -- степени при соответсвующих переменных, не 
*превышают десяти. Также структура содержит конструктор инициализации, использующий
* список инициализации, и указатель на следующий моном.
*/
struct monom
{
	double a; // coefficent
	int xyz; // deg_coef
	monom * next;
	monom(double a, int xyz, monom* next) : a(a), xyz(xyz), next(next) {};
};

/*Класс polinom обеспечивает хранение и взаимодействие со списком мономов. В качестве
* полей класс использует фиктивный узел nil, не содержащий данных, а только облегчающий
* проверки на краевые случаи, и указатель на голову списка.
*/
class polinom
{
private:
	monom* head;
	monom nil;
public:
    //Конструктор без параметров.Создает "пустой" список с фиктивным узлом.
	polinom() :nil(-1, 1000, &nil), head(&nil) {};

	~polinom();

	polinom(const polinom & right);

	const polinom &operator =(const polinom& right);

	//Функция вставки в список монома
	void push(double a, int xyz);

	polinom operator +(const polinom& right);

	polinom operator *(double a);

	polinom operator -(const polinom& right);

	polinom operator *(const polinom& right);
	
	friend std::ostream& operator<<(std::ostream& os, const polinom& p);

	monom* begin();

	monom* end();
};