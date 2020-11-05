#ifndef PILA_ESTATICA_H_INCLUDED
#define PILA_ESTATICA_H_INCLUDED
#include <iostream>
#include <stdexcept>
#include "LISTA_ESTATICA.h"

//Utiliza los métodos y estructura de una lista estática
//adaptados de forma que LiFo se cumpla

using namespace std;

template<size_t n,typename T>
class Pila_Estatica
{
    public:
        Pila_Estatica(){};
        //virtual ~Pila_Estatica();

        bool empty() const;
        bool full() const;
        int size() const;
        const T& top() const;
        void push(const T &valor);
        void pop();


    protected:

    private:
        ListaEstatica<n, T> list;

};

//SI ESTA VACIA
template<size_t n,  typename T>
bool Pila_Estatica<n, T>::empty()const
{
    return list.empty();
}

template<size_t n,  typename T>
bool Pila_Estatica<n, T>::full()const
{
    return list.full();
}
//VALIDAR SI ESTA LLENA
template<size_t n,  typename T>
int Pila_Estatica<n, T>::size()const
{
    return list.size();
}

//RETORNAR TOPE - CIMA
template<size_t n,  typename T>
const T& Pila_Estatica<n, T>::top() const
{
        if(empty())
            throw range_error("Trying top() on empty stack");
        return list.back();
}

template<size_t n,  typename T>
void Pila_Estatica<n, T>::push(const T &valor)
{
    if(full())
        throw range_error("Trying push(const T &value) on full stack");

    return list.push_back(valor); //INSERCION AL FINAL DE LA LISTA
}

template<size_t n,  typename T>
void Pila_Estatica<n, T>::pop()
{
    if(empty())
        throw range_error("Trying push(const T &value) on empty stack");
    return list.pop_back(); //ELIMINACION DEL ULTIMO ELEMENTO DE LA LISTA

}


#endif // Pila_Estatica_H_INCLUDED
