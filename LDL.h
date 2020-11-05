#ifndef LDL_H_INCLUDED
#define LDL_H_INCLUDED
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class LDL
{
private:
    struct NodoLDL
    {
        T dato;
        NodoLDL *siguiente, *anterior;
        NodoLDL(const T& element, NodoLDL* sig=nullptr, NodoLDL* ant=nullptr)
        {
            dato=element;
            siguiente=sig;
            anterior=ant;
        }
    };
    size_t listSize;
    NodoLDL *listFront, *listBack;

public:

    LDL()
    {
        listSize= 0;
        listBack = nullptr;
        listFront = nullptr;
    }

    LDL(const LDL& other)
    {
        listSize=0;
        listBack=nullptr;
        listFront=nullptr;
        for(size_t i(0); i<other.size();++i)
            push_back(other[i]);
    }

    LDL& operator = (const LDL& other)
    {
        listSize=0;
        listFront=nullptr;
        listBack=nullptr;
        for(size_t i(0); i < other.size();++i)
            push_back(other[i]);
        return *this;
    }

    ~LDL()
    {
        clear();
    }

    bool empty()const;
    size_t size()const;
    void push_front(const T& element);
    void push_back(const T& element);
    const T& front()const;
    const T& back()const;
    void pop_front();
    void pop_back();
    void insert(size_t position, const T& element);
    void erase(size_t position);
    void clear();
    void remove(const T& valor);
    T& operator[](size_t index) const;
};

template<typename T>
bool LDL<T>::empty()const
{
    return listSize==0;
}

template<typename T>
size_t LDL<T>::size()const
{
    return listSize;
}

template<typename T>
void LDL<T>::push_front(const T& element)
{
    if(empty())
    {
        listFront=new NodoLDL(element);
        listBack=listFront;
    }
    else
    {
        NodoLDL* nuevo= new NodoLDL(element,listFront);
        listFront->anterior=nuevo;
        listFront=nuevo;
    }
    listSize++;
}

template<typename T>
void LDL<T>::push_back(const T& element)
{
    if(empty())
    {
        listFront=new NodoLDL(element);
        listBack=listFront;
    }
    else
    {
        NodoLDL* nuevo=new NodoLDL(element,nullptr,listBack);
        listBack->siguiente=nuevo;
        listBack=nuevo;
    }
    listSize++;
}

template<typename T>
const T& LDL<T>::front()const
{
    if(empty())
        throw range_error("front() on empty list");
    return listFront->dato;
}

template<typename T>
const T& LDL<T>::back()const
{
    if(empty())
        throw range_error("back() on empty list");
    return listBack->dato;
}

template<typename T>
void LDL<T>::pop_front()
{
    if(empty())
        throw range_error("pop_front() on empty list");
    NodoLDL* eliminar=listFront;
    listFront=listFront->siguiente;
    listFront->anterior=nullptr;
    eliminar->siguiente=nullptr;
    delete eliminar;
    eliminar=nullptr;
    listSize--;
}

template<typename T>
void LDL<T>::pop_back()
{
    if(empty())
        throw range_error("pop_back() on empty list");
    NodoLDL* eliminar=listBack;
    listBack=listBack->anterior;
    listBack->siguiente=nullptr;
    eliminar->anterior=nullptr;
    delete eliminar;
    listSize--;
}

template <typename T>
void LDL<T>::insert(size_t position, const T& elemento)
{
    if(position > listSize||position < 0)
        throw range_error("Insert() in on non valid position");
    if(position == 0)
        push_front(elemento);
    else if(position == listSize)
        push_back(elemento);
    else
    {
        NodoLDL* temporal = listFront;
        for(size_t i(0); i < position-1;++i)
            temporal = temporal->siguiente;
        NodoLDL* nuevo = new NodoLDL(elemento,temporal->siguiente,temporal);
        NodoLDL* temporal2= temporal->siguiente;
        temporal->siguiente= nuevo;
        temporal2->anterior=nuevo;
        ++listSize;
    }
}

template<typename T>
void LDL<T>::erase(size_t position)
{
    if(empty())
        throw range_error("erase() on empty list");
    if(position >= listSize || position < 0)
        throw range_error("erase() in non valid position");
    else if(position == 0)
        pop_front();
    else if(position == listSize-1)
        pop_back();
    else
    {
        NodoLDL* temporal = listFront;
        for(size_t i(0); i < position-1;++i)
        {
         temporal= temporal->siguiente;
        }
        NodoLDL* eliminar = temporal->siguiente;
        temporal->siguiente=eliminar->siguiente;
        NodoLDL* temporal2=eliminar->siguiente;
        temporal2->anterior=temporal;
        delete eliminar;
        eliminar= nullptr;
        --listSize;
    }
}

template<typename T>
void LDL<T>::clear()
{
    for(size_t i(0); i < listSize; ++i)
        pop_front();
    listSize=0;
    listFront=nullptr;
    listBack=nullptr;
}

template<typename T>
void LDL<T>::remove(const T& valor)
{
    if(empty())
        throw range_error("remove() on empty list");
    NodoLDL* temporal = listFront;
    size_t i = 0;
    T dato;
    while(temporal != nullptr)
    {
        dato = temporal->dato;
        temporal=temporal->siguiente;
        if(dato == valor)
        {
            erase(i);
            --i;
        }
        ++i;
    }
}

template<typename T>
T& LDL<T>::operator[](size_t index) const
{
    if(empty())
        throw range_error("[] in empty list");
    if(index >= listSize || index < 0)
        throw range_error("[] in non valid position");
    NodoLDL* temporal= listFront;
    for(size_t i(0); i < index; ++i)
        temporal=temporal->siguiente;
    return temporal->dato;
}

#endif // LDL_H_INCLUDED
