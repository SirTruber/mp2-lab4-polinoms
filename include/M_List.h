#pragma once
#include <iostream>
/* ��������� monom ������������ �������� ����������� ������, ���������� �������
* ���������� � ���� ����������� ���������� ������ ����� � ���� 100*log_x(X)+10*
* *10*log_y(Y)+log_z(Z). X,Y,Z -- ������� ��� �������������� ����������, �� 
*��������� ������. ����� ��������� �������� ����������� �������������, ������������
* ������ �������������, � ��������� �� ��������� �����.
*/
struct monom
{
	double a; // coefficent
	int xyz; // deg_coef
	monom * next;
	monom(double a, int xyz, monom* next) : a(a), xyz(xyz), next(next) {};
};

/*����� polinom ������������ �������� � �������������� �� ������� �������. � ��������
* ����� ����� ���������� ��������� ���� nil, �� ���������� ������, � ������ �����������
* �������� �� ������� ������, � ��������� �� ������ ������.
*/
class polinom
{
private:
	monom* head;
	monom nil;
public:
    //����������� ��� ����������.������� "������" ������ � ��������� �����.
	polinom() :nil(-1, 1000, &nil), head(&nil) {};

	~polinom();

	polinom(const polinom & right);

	const polinom &operator =(const polinom& right);

	//������� ������� � ������ ������
	void push(double a, int xyz);

	polinom operator +(const polinom& right);

	polinom operator *(double a);

	polinom operator -(const polinom& right);

	polinom operator *(const polinom& right);
	
	friend std::ostream& operator<<(std::ostream& os, const polinom& p);

	monom* begin();

	monom* end();
};