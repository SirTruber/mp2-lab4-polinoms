#include "../include/M_List.h"

polinom::~polinom() 
{
    while (head != &nil)
    {
        monom * temp = head->next;
        delete head;
        head = temp;
    }
    nil.next = nullptr;
}

polinom::polinom(const polinom& right) : nil(1,1000,nullptr)
{
    this->~polinom();
    monom* tmp = right.head;
    while (tmp != &right.nil)
    {
        head = new monom(tmp->a, tmp->xyz, head);
        tmp = tmp->next;
    }
    nil.next = head;
};

const polinom &polinom::operator=(const polinom& right)
{
    if (this != &right) {
        this->~polinom();
        monom* tmp = right.head;
        while (tmp != &right.nil)
        {
            head = new monom(tmp->a, tmp->xyz, head);
            tmp = tmp->next;
        }
        nil.next = head;
    }
    return *this;
};

void polinom::push(double a, int xyz) 
{
    monom* tmp = head;
    while (xyz > tmp->next->xyz)
    {
        tmp = tmp->next;
    }

    if (xyz == tmp->xyz)
    {
        if (a != 0)
        {
            tmp->a = a;
        }
        else
        {
            monom* mov = tmp->next;
            while (mov->next != tmp)
            {
                mov = mov->next;
            }
            mov->next = tmp->next;
            delete tmp;
        }
    }

    if (tmp == head && xyz < head->xyz && a!= 0) 
    {
        head = new monom(a, xyz, head);
        nil.next = head;
        return;
    }

    if (a != 0 && xyz != tmp->xyz)
    {
        monom* pad = new monom(a, xyz, tmp->next);
        tmp->next = pad;
    }
};

polinom polinom::operator +(const polinom& right)
{
    polinom fus;
    monom* first = this->head;
    monom* second = right.head;
    while (first != &this->nil || second != &right.nil)
    {
        if (first->xyz < second->xyz)
        {
            fus.push(first->a, first->xyz);
            first = first->next;
        }

        if (first->xyz > second->xyz)
        {
            fus.push(second->a, second->xyz);
            second = second->next;
        }
        if (first->xyz == second->xyz)
        {
            fus.push(first->a + second->a, first->xyz);
            first = first->next;
            second = second->next;
        }
    }
    while (first != &this->nil)
    {
        fus.push(first->a, first->xyz);
        first = first->next;
    }

    while(second != &right.nil)
    {
        fus.push(second->a, second->xyz);
        second = second->next;
    }

    return fus;
};

polinom polinom::operator *(double a)
{
    polinom fus;
    for (monom* tmp = head; tmp != &this->nil; tmp = tmp->next)
    {
        fus.push(tmp->a * a, tmp->xyz);
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
    for(monom* i = this->head;i != &this->nil; i = i->next)
    {
        polinom add;
        for (monom* j = right.head; i != &right.nil; j = j->next) {
            int deg = i->xyz + j->xyz;
            if (deg / 100 < i->xyz / 100) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow x-degree");
            if (deg / 10 % 10 < i->xyz / 10 % 10) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow y-degree");
            if (deg % 10 < i->xyz % 10) throw std::out_of_range("polinom polinom::operator *(const polinom& right).Overflow z-degree");

            add.push(i->a * j->a, i->xyz + j->xyz);
        }
        fus = fus + add;
    }
    
    return fus;
};

std::ostream& operator<<(std::ostream& os, const polinom& p) 
{
    for (monom* tmp = p.head; tmp != &p.nil; tmp = tmp->next) 
    {
        int x = tmp->xyz / 100;
        int y = tmp->xyz / 10 % 10;
        int z = tmp->xyz % 10;

        std::cout << tmp->a;
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
                std::cout << "(" << tmp->xyz % 10 << ")";
            }
        }
        if (tmp->next->a > 0)
        {
            std::cout << " + ";
        }
    }
    return os;
};

monom* polinom::begin()
{
    return head;
};

monom* polinom::end()
{
    return &nil;
}