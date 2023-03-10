#include <gtest.h>
#include "M_List.h"

TEST(polinomials, can_create_polinom)
{
	ASSERT_NO_THROW(polinom p);
}

TEST(polinomials, expect_that_empty_polinom_has_no_monoms)
{
	polinom p;
	int i = 0;
	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++);
	EXPECT_EQ(i, 0);
};

TEST(polinomials, can_copy_polinoms)
{
	polinom p1;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);
	double a[3] = { 1,2,1 };
	int xyz[3] = {20, 110, 200};
	polinom p2(p1);

	for (monom* tmp = p2.begin(); tmp != p2.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, expect_that_copyed_polinoms_has_own_memory)
{
	polinom p1;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);
	polinom p2(p1);

	EXPECT_NE(&p1,&p2);
};

TEST(polinomials, assign_can_change_polinoms)
{
	polinom p1;
	polinom p2;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);
	//p2 = 2 + z
	p2.push(1, 001);
	p2.push(2, 000);
	p1 = p2;

	int i = 0;
	for (monom* tmp = p1.begin(); tmp != p1.end(); tmp = tmp->next, i++);
	EXPECT_EQ(2,i);
};

TEST(polinomials, can_assign_to_yourself)
{
	polinom p;

	//p = y^2 + 2xy + x^2
	p.push(1, 200);
	p.push(2, 110);
	p.push(1, 20);
	
	ASSERT_NO_THROW(p = p);
};

TEST(polinomials, can_insert_monomes)
{
	polinom p;

	ASSERT_NO_THROW(p.push(2.1,10));
};

TEST(polinomials, zero_monomes_are_not_stored)
{
	polinom p;
	int i = 0;

	p.push(0, 200);
	p.push(0, 110);
	p.push(0, 20);

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++);
	EXPECT_EQ(0, i);
};

TEST(polinomials, simular_monomes_are_replaced_when_entering)
{
	polinom p;
	int i = 0;

	//p = x^2
	p.push(1, 200);
	
	//p = 3x^2
	p.push(3, 200);

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++);
	
	EXPECT_TRUE(p.begin()->a == 3. 
		     && p.begin()->xyz == 200
	         && i == 1);
};

TEST(polinomials, replace_to_zero_monom_can_delete)
{
	polinom p;
	int i = 0;

	//p = y^2 + 2xy + x^2
	p.push(1, 200);
	p.push(2, 110);
	p.push(1, 20);

	//p = 2xy
	p.push(0, 200);
	p.push(0, 20);

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++);
	EXPECT_EQ(1, i);
}; 

TEST(polinomials, can_sum_polinoms)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);

	//p2 = z^3 -2xy 
	p2.push(-2, 110);
	p2.push(1, 3);

	//p = z^3 + y^2 + x^2
	polinom p = p1 + p2;

	double a[3] = { 1,1,1 };
	int xyz[3] = { 3, 20, 200 };
	
	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, can_add_to_empty_polinom)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);

	p2 = p1 + p2;

	double a[3] = { 1,2,1 };
	int xyz[3] = { 20, 110, 200 };

	for (monom* tmp = p2.begin(); tmp != p2.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, can_sub_polinomials)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	p1.push(1, 20);

	//p2 = z^3 -2xy 
	p2.push(-2, 110);
	p2.push(1, 003);

	//p = -z^3 + y^2 + 4xy + x^2
	polinom p = p1 - p2;

	double a[4] = { -1,1,4,1 };
	int xyz[4] = { 3, 20,110, 200 };

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(4, i);
};

TEST(polinomials, sub_from_itself_gives_zero)
{
	polinom p;
	int i = 0;

	//p = y^2 + 2xy + x^2
	p.push(1, 200);
	p.push(2, 110);
	p.push(1, 20);

	p = p - p;

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++);
	
	EXPECT_EQ(0, i);
};

TEST(polinomials, can_mult_polinomials_to_number)
{
	polinom p;
	int i = 0;

	//p = 2y^2 + 4xy + 2x^2
	p.push(1, 200);
	p.push(2, 110);
	p.push(1, 20);
	p = p * 2;

	double a[3] = { 2,4,2 };
	int xyz[3] = { 20,110, 200 };

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, mult_to_zero_gives_empty_polinomial)
{
	polinom p;
	int i = 0;
	int j = 0;
	int k = 0;

	//p = y^2 + 2xy + x^2
	p.push(1, 200);
	p.push(2, 110);
	p.push(1, 20);

	polinom empty;
	polinom p1 = p * 0;
	polinom p2 = p * empty;
	polinom p3 = empty * p;

	for (monom* tmp = p1.begin(); tmp != p1.end(); tmp = tmp->next, i++);
	for (monom* tmp = p2.begin(); tmp != p2.end(); tmp = tmp->next, j++);
	for (monom* tmp = p3.begin(); tmp != p3.end(); tmp = tmp->next, k++);

	EXPECT_TRUE(i == 0 && j == 0 && k == 0);
};

TEST(polinomials, can_mult_polinomial_to_polinomial)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = 2xy + x^2
	p1.push(1, 200);
	p1.push(2, 110);
	
	//p2 = z^3 -2xy 
	p2.push(-2, 110);
	p2.push(1, 003);

	//p = 2xyz^3 + x^2z^3 -4x^2y^2 -2x^3y
	polinom p = p1 * p2;

	double a[4] = { 2, 1,-4,-2 };
	int xyz[4] = { 113, 203,220, 310 };

	for (monom* tmp = p.begin(); tmp != p.end(); tmp = tmp->next, i++)
	{
		if (tmp->a != a[i] || tmp->xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(4, i);
};

TEST(polinomials, throw_when_overflow_degree)
{
	polinom p1, p2,p;
	int i = 0;

	//p1 = y^2 + 2xy + x^7
	p1.push(1, 700);
	p1.push(2, 110);
	p1.push(1, 20);

	//p2 = x^4
	p2.push(1, 400);

	ASSERT_ANY_THROW(p = p1 * p2);
};