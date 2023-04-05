#pragma once
#include <iostream>

// Контейнер monom обеспечивает хранение монома
struct monom
{
    double         _a;       // Коэффицент монома
    int            _xyz;     // Степени переменных в виде 100x + 10y + z. Степени не выше десяти

    /*\brief Конструктор со списком инициализаторов элементов
    * \param a Коэффицент монома
    * \param xyz Степени переменных
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

// Структура хранения отсортированного списка 
template<typename T>
class sortedList
{
private:
    // Вершины, хранящие произвольные типы данных
    struct node
    {
        T          _data = T();        // Данные 
        node *     _next = nullptr;    // Указатель на следующий элемент
    };
    node* _head;   // Указатель на голову 
    node  _nil;    // Фиктивный узел
public:
    // Создает "пустой" список с фиктивным узлом
    sortedList() :
        _head(&_nil),
        _nil{ T(), &_nil }
    {};

    // Деструктор
    ~sortedList()
    {
        while (_head != &_nil)
        {
            popMin();
        }
        _nil._next = nullptr;
    };

    //\brief Конструктор копии
    //\param right Копируемый список
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
    //\brief Оператор присваивания
    //\param right Копируемый список
    //\return Константная ссылка на скопированный список
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
    
    //\brief Вставка с упорядочиванием
    //\param data Данные для вставки
    void push(const T data)
    {
        node* cur = &_nil;

        // Сдвигаем указатель, пока не дойдем до края или данные не превысят порог 
        while (cur->_next != &_nil && cur->_next->_data < data)
        {
            cur = cur->_next;
        }

        // если данные совпадают, нужно либо заместить данные, либо удалить, если они нулевые
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
        
        // Если данные ненулевые, вставляем их между отсортированными промежутками
        // и перепривязываем указатели
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

    //\brief Метод, удаляющий минимальный элемент
    //\return Минимальный элемент
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
    // \brief Получение первого элемента списка
    // \return Указатель на первый элемент
    iterator begin() const { return iterator(_head); };
    // \brief Получение конца списка
    // \return Указатель на один элемент после последнего
    iterator end()   const { return iterator(&_nil); };

};
using ItemIterator = typename sortedList<monom>::iterator;
//Класс polinom обеспечивает хранение и взаимодействие со списком мономов.
class polinom
{
private:
    sortedList<monom> _list ;
public:
    //Конструктор без параметров.Создает "пустой" список с фиктивным узлом.
    polinom() = default;

    //Деструктор
    ~polinom() = default;

    //\brief Конструктор копии 
    //\param right Копируемый полином
    polinom(const polinom & right);

    //\brief Конструктор копии 
    //\param right Копируемый полином
    const polinom &operator =(const polinom& right);

    //\brief Метод вставки в полином монома
    //\param data Моном для вставки
    void push(monom data);

    polinom operator +(const polinom& right);

    polinom operator *(double a);

    polinom operator -(const polinom& right);

    polinom operator *(const polinom& right);
    //\brief Процедура вывода полинома на экран
    void show();

    ItemIterator begin() const;
    ItemIterator end() const;
    ItemIterator& next(ItemIterator &it);
    ItemIterator operator++(int);
};