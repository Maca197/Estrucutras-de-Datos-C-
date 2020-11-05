#ifndef COLA_ESTATICA_H_INCLUDED
#define COLA_ESTATICA_H_INCLUDED
#include <iostream>
#include <stdexcept>

using namespace std;

const size_t CAPACITY = 1000;

template< typename T, size_t n = CAPACITY>
class Cola_Estatica
{
    public:
        Cola_Estatica()
        {
            frontIndex = 0;
            backIndex = 0;
            containerSize = n;
            queueSize = 0;
            cout<<containerSize;
        }
        bool empty() const;
        bool full() const;
        size_t size() const;
        const T& front() const; //referencia constante de t y metodo tipo constante
        const T& back() const;
        void push(const T& element);
        void pop();

    private:
        T elements[CAPACITY];
        size_t frontIndex;
        size_t backIndex;
        size_t containerSize;
        size_t queueSize;
};
//VACIA?
template<typename T, size_t n>
bool Cola_Estatica<T, n>::empty() const
{
    return queueSize == 0;
}
//LLENA?
template<typename T, size_t n>
bool Cola_Estatica<T, n>::full() const
{
    return queueSize == containerSize;
}
//TAMAÑO ACTUAL?  NUMERO DE ELEMENTOS AÑADIDOS
template<typename T, size_t n>
size_t Cola_Estatica<T, n>::size() const
{
    return queueSize;
}
//FRENTE?
template<typename T, size_t n>
const T& Cola_Estatica<T, n>::front() const
{
    if(empty())
        throw range_error("Trying front() on empty queue");
    return elements[frontIndex];
}
//REVERSO?
template<typename T, size_t n>
const T& Cola_Estatica<T, n>::back() const
{
    if(empty())
        throw range_error("Trying back() on empty queue");
    if(backIndex == 0)
        return elements[containerSize-1];
    else
        return elements[backIndex-1];

}
//AÑADIR ELEMENTOS
template<typename T, size_t n>
void Cola_Estatica<T,n>::push(const T& element)
{
    if(full())
        throw range_error("Trying push(const &element) on full queue");
    elements[backIndex] = element;
    backIndex = (backIndex +1) % containerSize; //HACE CIRCULAR LA COLA, EN CASO DE QUE HAYA LLEGADO AL ULTIMO URA AL FINAL
    ++queueSize;
}
//ELIMINAR ELEMENTOS
template<typename T, size_t n>
void Cola_Estatica<T, n>::pop()
{
    if (empty())
        throw range_error("Trying pop() on empty queue");
    frontIndex = (frontIndex + 1) % containerSize,
    --queueSize;
}
#endif // COLA_ESTATICA_H_INCLUDED
