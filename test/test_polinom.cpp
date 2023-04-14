#include <gtest.h>
#include "M_List.h"

TEST(list, can_create_list)
{
	ASSERT_NO_THROW(sortedList<int> l);
}

TEST(list, can_copy_list)
{
	sortedList<int> l1;
	
	l1.push(1);
	sortedList<int>l2(l1);

	EXPECT_EQ(1, l2.popMin());
}

TEST(list, expect_that_copyed_list_has_own_memory)
{
	sortedList<int> l1;

	l1.push(1);
	sortedList<int>l2(l1);
	
	EXPECT_NE(&l1,&l2);
}

TEST(list, can_assign_list)
{
	sortedList<int> l1;
	sortedList<int> l2;

	l1.push(1);
	l2 = l1;

	EXPECT_EQ(1, l2.popMin());
}

TEST(list, can_assign_yourself)
{
	sortedList<int> l;

	l.push(2); l.push(3);

	ASSERT_NO_THROW(l = l);
}

TEST(list, can_push)
{
	sortedList<int> l;
	ASSERT_NO_THROW(l.push(100));
}

TEST(list, can_pop)
{
	sortedList<int> l;

	l.push(1);

	ASSERT_NO_THROW(l.popMin());
}

TEST(list, expect_throw_when_pop_empty_list)
{
	sortedList<int> l;

	ASSERT_ANY_THROW(l.popMin());
}

TEST(polinomials, can_create_polinom)
{
	ASSERT_NO_THROW(polinom p);
}

TEST(polinomials, expect_that_empty_polinom_has_no_monoms)
{
	polinom p;
	int i = 0;
	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++);
	EXPECT_EQ(i, 0);
};

TEST(polinomials, can_copy_polinoms)
{
	polinom p1;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });
	double a[3] = { 1,2,1 };
	int xyz[3] = {20, 110, 200};
	polinom p2(p1);

	for (ItemIterator tmp = p2.begin(); tmp != p2.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, expect_that_copyed_polinoms_has_own_memory)
{
	polinom p1;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });
	polinom p2(p1);

	EXPECT_NE(&p1,&p2);
};

TEST(polinomials, assign_can_change_polinoms)
{
	polinom p1;
	polinom p2;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });
	//p2 = 2 + z
	p2.push(monom{ 1, 1 });
	p2.push(monom{ 2, 0 });
	p1 = p2;

	int i = 0;
	for (ItemIterator tmp = p1.begin(); tmp != p1.end(); ++tmp, i++);
	EXPECT_EQ(2,i);
};

TEST(polinomials, can_assign_to_yourself)
{
	polinom p;

	//p = y^2 + 2xy + x^2
	p.push(monom{ 1, 200 });
	p.push(monom{ 2, 110 });
	p.push(monom{ 1, 20 });
	
	ASSERT_NO_THROW(p = p);
};

TEST(polinomials, can_insert_monomes)
{
	polinom p;

	ASSERT_NO_THROW(p.push(monom{ 2.1,10 }));
};
TEST(polinomials, can_insert_many_monoms)
{
	polinom p;

	ASSERT_NO_THROW(for (int i = 0; i < 1000; i++) p.push(monom{pow(i,2),i}););
}
TEST(polinomials, zero_monomes_are_not_stored)
{
	polinom p;
	int i = 0;

	p.push(monom{ 0, 200 });
	p.push(monom{ 0, 110 });
	p.push(monom{ 0, 20 });

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++);
	EXPECT_EQ(0, i);
};

TEST(polinomials, simular_monomes_are_reduced_when_entering)
{
	polinom p;
	int i = 0;

	//p = x^2
	p.push(monom{ 1, 200 });
	
	//p = 3x^2
	p.push(monom{ 3, 200 });
	p.butifie();
	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++);
	
	EXPECT_TRUE(p.begin()->_a == 4. 
		     && p.begin()->_xyz == 200
	         && i == 1);
};

TEST(polinomials, padding_to_zero_monom_can_delete)
{
	polinom p;
	int i = 0;

	//p = y^2 + 2xy + x^2
	p.push(monom{ 1, 200 });
	p.push(monom{ 2, 110 });
	p.push(monom{ 1, 20 });

	//p = 2y^2 + 2xy
	p.push(monom{ -1, 200 });
	p.push(monom{ 1, 20 });
	p.butifie();
	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++);
	EXPECT_EQ(2, i);
}; 

TEST(polinomials, can_sum_polinoms)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });

	//p2 = z^3 -2xy 
	p2.push(monom{ -2, 110 });
	p2.push(monom{ 1, 3 });

	//p = z^3 + y^2 + x^2
	polinom p = p1 + p2;

	double a[3] = { 1,1,1 };
	int xyz[3] = { 3, 20, 200 };
	
	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, can_add_to_empty_polinom)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });

	p2 = p1 + p2;

	double a[3] = { 1,2,1 };
	int xyz[3] = { 20, 110, 200 };

	for (ItemIterator tmp = p2.begin(); tmp != p2.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
};

TEST(polinomials, can_sub_polinomials)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = y^2 + 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });

	//p2 = z^3 -2xy 
	p2.push(monom{ -2, 110 });
	p2.push(monom{ 1, 003 });

	//p = -z^3 + y^2 + 4xy + x^2
	polinom p = p1 - p2;

	double a[4] = { -1,1,4,1 };
	int xyz[4] = { 3, 20,110, 200 };

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(4, i);
};

TEST(polinomials, sub_from_itself_gives_zero)
{
	polinom p;
	int i = 0;

	//p = y^2 + 2xy + x^2
	p.push(monom{ 1, 200 });
	p.push(monom{ 2, 110 });
	p.push(monom{ 1, 20 });

	p = p - p;

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++);
	
	EXPECT_EQ(0, i);
};

TEST(polinomials, can_mult_polinomials_to_number)
{
	polinom p;
	int i = 0;

	//p = 2y^2 + 4xy + 2x^2
	p.push(monom{ 1, 200 });
	p.push(monom{ 2, 110 });
	p.push(monom{ 1, 20 });
	p = p * 2;

	double a[3] = { 2,4,2 };
	int xyz[3] = { 20,110, 200 };

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
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
	p.push(monom{ 1, 200 });
	p.push(monom{ 2, 110 });
	p.push(monom{ 1, 20 });

	polinom empty;
	polinom p1 = p * 0;
	polinom p2 = p * empty;
	polinom p3 = empty * p;

	for (ItemIterator tmp = p1.begin(); tmp != p1.end(); ++tmp, i++);
	for (ItemIterator tmp = p2.begin(); tmp != p2.end(); ++tmp, j++);
	for (ItemIterator tmp = p3.begin(); tmp != p3.end(); ++tmp, k++);

	EXPECT_TRUE(i == 0 && j == 0 && k == 0);
};

TEST(polinomials, can_mult_polinomial_to_polinomial)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });
	
	//p2 = z^3 -2xy 
	p2.push(monom{ -2, 110 });
	p2.push(monom{ 1, 003 });

	//p = 2xyz^3 + x^2z^3 -4x^2y^2 -2x^3y
	polinom p = p1 * p2;

	double a[4] = { 2, 1,-4,-2 };
	int xyz[4] = { 113, 203,220, 310 };

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(4, i);
};

TEST(polinomials, mult_polinomial_to_polinomial_reduced_simular)
{
	polinom p1;
	polinom p2;
	int i = 0;

	//p1 = 2xy + x^2
	p1.push(monom{ 1, 200 });
	p1.push(monom{ 2, 110 });

	//p2 = 2x^2 - 6xy 
	p2.push(monom{ 2, 200 });
	p2.push(monom{ -6, 110 });

	//p = -12x^2y^2 - 2x^3y + 2x^4   
	polinom p = p1 * p2;

	double a[3] = { -12, -2,2};
	int xyz[3] = { 220, 310, 400 };

	for (ItemIterator tmp = p.begin(); tmp != p.end(); ++tmp, i++)
	{
		if (tmp->_a != a[i] || tmp->_xyz != xyz[i]) FAIL();
	}
	EXPECT_EQ(3, i);
}

TEST(polinomials, throw_when_overflow_degree)
{
	polinom p1, p2,p;
	int i = 0;

	//p1 = y^2 + 2xy + x^7
	p1.push(monom{ 1, 700 });
	p1.push(monom{ 2, 110 });
	p1.push(monom{ 1, 20 });

	//p2 = x^4
	p2.push(monom{ 1, 400 });

	ASSERT_ANY_THROW(p = p1 * p2);
};