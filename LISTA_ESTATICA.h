#ifndef LISTA_ESTATICA_H_INCLUDED
#define LISTA_ESTATICA_H_INCLUDED
#include <iostream>
#include <stdexcept> //permite lanzar excepciones

using namespace std;

//Indica qie la clase será una plantilla
template<size_t n, typename T>  //size_t: entero sin signo  //typename: Indica el tipo de dato que será reemplazado en ejecucion
class ListaEstatica
{
    public:
        ListaEstatica ()
        {
            if(n > CAPACITY)
                throw invalid_argument("Non valid list size, lol");
            index = 0;
            containerSize = n;
        }

        bool empty() const;
        bool full() const;
        size_t size() const;
        void push_front(const T& element);
        void push_back(const T& element);
        const T& front() const;
        const T& back() const;
        void pop_front();
        void pop_back();
        void insert(size_t position, const T& element);
        void erase(size_t position);
        T&  operator[](size_t position);//sobrecarga
        void clear();
        void remove(const T& value);

        private:
            static const size_t CAPACITY =   1000;
            T elements[CAPACITY];
            size_t index;
            size_t containerSize;

};

//LISTA VACIA?
template<size_t n, typename T>
bool ListaEstatica<n, T>::empty() const
{
    return index == 0;
}

//LISTA LLENA?
template<size_t n, typename T>
bool ListaEstatica<n, T>::full() const
{
    return index == containerSize;
}

//TAMAÑO de elementos guardados en el arreglo
template<size_t n, typename T>
size_t ListaEstatica<n, T>::size() const
{
   return index;
}

//INSERCCION AL INICIO
template<size_t n, typename T>
void ListaEstatica<n, T>::push_front(const T &element)
{
    if(full())
        throw range_error("Trying push_front(const T& element)  on a full list");
    if(empty())
        elements[0] =  element;
    else
    {
        //RECORRIMIENTO DE LOS ELEMENTOS EN UNA POSICION
        for(size_t i(index); i > 0; --i)
            elements[i] = elements[i-1];
        //INSERCCION AL INICIO
        elements[0] =  element;

    }

    ++index;
}

//INSERCCION AL FINAL (despues del ultimo elemento)
template<size_t n, typename T>
void ListaEstatica<n, T>::push_back(const T &element)
{
    if(full())
        throw range_error("Trying push_back(const T& element)  on a full list");

    elements[index++] = element;    //elementd[index] = element;  index++;
}

//REGRESA EL ELEMENTO DEL FRENTE
template<size_t n, typename T>
const T& ListaEstatica<n, T>::front() const
{
    if(empty())
        throw range_error("Trying front() on a empty list");

    return elements[0];
}

//REGRESA EL ELEMENTO DE ATRÁS "FINAL"
template<size_t n, typename T>
const T& ListaEstatica<n, T>::back() const
{
    if(empty())
        throw range_error("Trying back() on a empty list");

    return elements[index-1];
}

//ELIMINA EL ELEMENTO DEL FRENTE
template<size_t n, typename T>
void ListaEstatica<n, T>::pop_front()
{
    if(empty())
        throw range_error("trying pop_front() on empty list");
    for(size_t i(0); i<index; i++) //i<index-1
        elements[i] =  elements[i+1];

    index--;
}

//ELIMINA EL ELEMENTO DEL ATRÁS
template<size_t n, typename T>
void ListaEstatica<n, T>::pop_back()
{
     if(empty())
        throw range_error("trying pop_back() on empty list");
    index--;

}

//INSERTA
template<size_t n, typename T>
void ListaEstatica<n, T>::insert(size_t position, const T &element)
{
    if(full())
        throw range_error("Trying insert(size_t position, const T &element) on full list");
    if(position > size())
         throw range_error("Trying insert(size_t position, const T &element) in non valid position");
    if(position == 0)
        push_front(element);
    else if(position == size())
        push_back(element);
    else
    {
        for(size_t i(index); i> position; i--)
            elements[i] = elements[i-1];
        elements[position] = element;
        index++;
    }

}
//BORRAR EN POSICION
template <size_t n, typename T>
void ListaEstatica<n,T>::erase(size_t position)
{
    if(empty())
        throw range_error("Trying erase(size_t position) on empty list");
    if(position >= size())
       throw range_error("Trying erase(size_t position) in non valid position");
    if(position == 0)
        pop_front();
    else if(position == size() -1)
        pop_back();
    else
    {
        for (size_t i(position); i<index-1; i++)
            elements[i] = elements[i+1];
        index--;
    }
}

//SOBRECARGA
template <size_t n, typename T>
T&  ListaEstatica<n,T>::operator[](size_t position)
{
    if(empty())
        throw range_error("Trying [] on empty list");
    if(position >= size())
    throw range_error("Trying [] in non valid position");
    return elements[position];
}
//ELIMINAR TODO
template <size_t n, typename T>
void  ListaEstatica<n,T>::clear()
{
    index = 0;
}

//REMOVER ELEMENTO ESPECIFICO
template <size_t n, typename T>
void ListaEstatica<n,T>::remove(const T& value)
{
    if(empty())
        throw range_error("Trying remove(const T& value) on empty list");

    size_t  i(0);
    while(i < index)
    {
        if(elements[i] == value)
        {
            erase(i);//borra y desplaza los demas elementos
            i--;
        }
        i++;
    }
}

#endif // LISTA_ESTATICA_H_INCLUDED
