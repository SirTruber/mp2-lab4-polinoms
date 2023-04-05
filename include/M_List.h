#pragma once
#include <iostream>

// ��������� monom ������������ �������� ������
struct monom
{
    double         _a;       // ���������� ������
    int            _xyz;     // ������� ���������� � ���� 100x + 10y + z. ������� �� ���� ������

    /*\brief ����������� �� ������� ��������������� ���������
    * \param a ���������� ������
    * \param xyz ������� ����������
    */
    monom(double a = -1, int xyz = 1000) :
        _a(a),
        _xyz(xyz)
    {};

    bool operator==(const monom& r) const { return _xyz == r._xyz; };
    bool operator!=(const monom& r) const { return _xyz != r._xyz; };
    bool operator<(const monom& r)  const { return _xyz < r._xyz; };
    bool operator<=(const monom& r) const { return _xyz <= r._xyz; };
    bool operator>(const monom& r)  const { return _xyz > r._xyz; };
    bool operator>=(const monom& r) const { return _xyz >= r._xyz; };

    bool operator==(const double& r)const { return _a == r; };
    bool operator!=(const double& r)const { return _a != r; };
};

// ��������� �������� ���������������� ������ 
template<typename T>
class sortedList
{
private:
    // �������, �������� ������������ ���� ������
    struct node
    {
        T          _data = T();        // ������ 
        node *     _next = nullptr;    // ��������� �� ��������� �������
    };
    node* _head;   // ��������� �� ������ 
    node  _nil;    // ��������� ����
public:
    // ������� "������" ������ � ��������� �����
    sortedList() :
        _head(&_nil),
        _nil{ T(), &_nil }
    {};

    // ����������
    ~sortedList()
    {
        while (_head != &_nil)
        {
            popMin();
        }
        _nil._next = nullptr;
    };

    //\brief ����������� �����
    //\param right ���������� ������
    sortedList(const sortedList<T>& right):
        _head(&_nil),
        _nil{ T(),&_nil }
    {
        if (right.begin() == right.end()) return;
        _head = new node{T(*right.begin()), &_nil};
        node * cur = _head;
        for (node * tmp = right._head->_next; tmp != &right._nil; tmp = tmp->_next )
        {
            cur->_next = new node{ T(tmp->_data), &_nil };
            cur = cur->_next;
        }
        _nil._next = _head;
    };
    //\brief �������� ������������
    //\param right ���������� ������
    //\return ����������� ������ �� ������������� ������
    const sortedList& operator=(const sortedList<T>& right)
    {
        if (this != &right)
        {
            this->~sortedList();
            if (right.begin() == right.end())
            {
                _nil._next = &_nil;
                return *this;
            }
            _head = new node{ T(*right.begin()), &_nil };
            node* cur = _head;
            for (node * tmp = right._head->_next; tmp != &right._nil; tmp = tmp->_next)
            {
                cur->_next = new node{ T(tmp->_data), &_nil };
                cur = cur->_next;
            }
            _nil._next = _head;
        }
        return *this;
    };
    
    //\brief ������� � ���������������
    //\param data ������ ��� �������
    void push(const T data)
    {
        node* cur = &_nil;

        // �������� ���������, ���� �� ������ �� ���� ��� ������ �� �������� ����� 
        while (cur->_next != &_nil && cur->_next->_data < data)
        {
            cur = cur->_next;
        }

        // ���� ������ ���������, ����� ���� ��������� ������, ���� �������, ���� ��� �������
        if (cur->_next->_data == data)
        {
            if (data != 0)
            {
                cur->_next->_data = data;
            }
            else
            {
                node* tmp = cur->_next;
                cur->_next = cur->_next->_next;
                if (tmp == _head) _head = _head->_next;
                delete tmp;
            }
            return;
        }
        
        // ���� ������ ���������, ��������� �� ����� ���������������� ������������
        // � ��������������� ���������
        if (data != 0) 
        {
            node* target = new node{data,cur->_next};
            
            cur->_next = target;
            if (target == _nil._next)
            {
                _head = target;
                _nil._next = _head;
            }
        }
    };

    //\brief �����, ��������� ����������� �������
    //\return ����������� �������
    T popMin()
    {
        if (_head == &_nil) throw std::underflow_error("underflow list");
        T target = _head->_data;
        node* tmp = _head->_next;
        delete _head;
        _head = tmp;
        return target;
    };
    
    class iterator {
    private:
        node* _me = nullptr;
    public:
        iterator(const node* r) { _me = const_cast< node* >(r); };
        iterator(const iterator& it) { _me = it._me; };
        T& operator*() { return _me->_data; };
        T* operator->() { return &_me->_data; }
        bool operator==(const iterator& it) { return _me == it._me; };
        bool operator!=(const iterator& it) { return _me != it._me; };

        iterator& operator++() { _me = _me->_next; return *this; };
        iterator operator++(int) { iterator r(*this); _me = _me->_next; return r; };
    };
    // \brief ��������� ������� �������� ������
    // \return ��������� �� ������ �������
    iterator begin() const { return iterator(_head); };
    // \brief ��������� ����� ������
    // \return ��������� �� ���� ������� ����� ����������
    iterator end()   const { return iterator(&_nil); };

};
using ItemIterator = typename sortedList<monom>::iterator;
//����� polinom ������������ �������� � �������������� �� ������� �������.
class polinom
{
private:
    sortedList<monom> _list ;
public:
    //����������� ��� ����������.������� "������" ������ � ��������� �����.
    polinom() = default;

    //����������
    ~polinom() = default;

    //\brief ����������� ����� 
    //\param right ���������� �������
    polinom(const polinom & right);

    //\brief ����������� ����� 
    //\param right ���������� �������
    const polinom &operator =(const polinom& right);

    //\brief ����� ������� � ������� ������
    //\param data ����� ��� �������
    void push(monom data);

    polinom operator +(const polinom& right);

    polinom operator *(double a);

    polinom operator -(const polinom& right);

    polinom operator *(const polinom& right);
    //\brief ��������� ������ �������� �� �����
    void show();

    ItemIterator begin() const;
    ItemIterator end() const;
    ItemIterator& next(ItemIterator &it);
    ItemIterator operator++(int);
};