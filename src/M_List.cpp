#include "../include/M_List.h"

polinom::polinom(const polinom& right) : 
    _list(right._list)
{};

const polinom &polinom::operator=(const polinom& right)
{
    if (this != &right) {
        _list = right._list;
    }
    return *this;
};

void polinom::push(monom data) 
{
    _list.push(data);
};

polinom polinom::operator +(const polinom& right)
{
    polinom fus;
    auto first = _list.begin();
    auto second = right._list.begin();
    while ( first != _list.end() && second != right._list.end())
    {
        if (*first < *second)
        {
            fus.push(*first);
            first ++;
            continue;
        }

        if (*first > *second)
        {
            fus.push(*second);
            second ++;
            continue;
        }
        
        fus.push(monom{ first->_a + second->_a,first->_xyz });
        first ++;
        second ++;
        continue;
        
    }
    while (first != _list.end())
    {
        fus.push(*first);
        first ++;
    }

    while(second != right._list.end())
    {
        fus.push(*second);
        second ++;
    }

    return fus;
};

polinom polinom::operator *(double a)
{
    polinom fus;
    for (auto tmp = _list.begin(); tmp != _list.end(); tmp++)
    {
        fus.push(monom{ tmp->_a * a,tmp->_xyz });
    }
    return fus;
};

polinom polinom::operator -(const polinom& right)
{
    polinom fus = right;
    return ((fus * -1.) + *this);
};

polinom polinom::operator *(const polinom& right) 
{
    polinom fus;
    for(auto i = _list.begin(); i != _list.end(); i++ )
    {
        if (right._list.begin() == right._list.end()) return fus; // для умножения на ноль справа
        polinom add;
        for (auto j = right._list.begin(); j != right._list.end(); j++ ) {
            int deg = i->_xyz + j->_xyz;
            if (deg / 100 % 10 < i->_xyz / 100) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow x-degree");
            if (deg / 10 % 10 < i->_xyz / 10 % 10) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow y-degree");
            if (deg % 10 < i->_xyz % 10) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow z-degree");

            
            add.push(monom{ i->_a * j->_a, i->_xyz + j->_xyz });
        }
        fus = fus + add;
    }
    
    return fus;
};

void polinom::show()
{
    for (auto tmp = _list.begin(); tmp != _list.end(); )
    {
        int x = tmp->_xyz / 100;
        int y = tmp->_xyz / 10 % 10;
        int z = tmp->_xyz % 10;
        
        if(tmp->_a != 1)
            std::cout << tmp->_a;
        if (x != 0)
        {
            std::cout << "x";
            if (x != 1)
            {
                std::cout << "^(" << x << ")";
            }
        }
        if (y != 0) {
            std::cout << "y";
            if (y != 1)
            {
                std::cout << "(" << y << ")";
            }
        }
        if (z != 0) {
            std::cout << "z";
            if (z != 1)
            {
                std::cout << "(" << tmp->_xyz % 10 << ")";
            }
        }

        tmp++;

        if (tmp->_a > 0)
        {
            std::cout << " + ";
        }
    }
}
ItemIterator polinom::begin() const
{
    return _list.begin();
}
ItemIterator polinom::end() const
{
    return _list.end();
}
ItemIterator& polinom::next(ItemIterator &it)
{
    return it.operator++();
};