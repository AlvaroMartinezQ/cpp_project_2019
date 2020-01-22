/**
* Modulo: IteradorLista
* Tipo: Programa() Interfaz-Implementacion TAD (X)       Otros()
* Autor: José Miguel Buenaposada (josemiguel.buenaposada@urjc.es)
* Fecha: 2015
* Descripción: Implementación de los iteradores para el TAD Lista
*/

#ifndef nullptr
#define nullptr NULL
#endif

#include "lista.hpp"

template <typename E>
bool IteradorLista<E>::permiteIterarAscendente()
{
  return true;
}

template <typename E>
bool IteradorLista<E>::permiteIterarDescendente()
{
  return true;
}

template <typename E>
bool IteradorLista<E>::permiteInsertar()
{
  return true;
}

template <typename E>
bool IteradorLista<E>::permiteEliminar()
{
  return true;
}

template <typename E>
void IteradorLista<E>::obtenerElemento(E& e)
{
  if (!esIteradorValido())
  {
    throw EIteradorNoValido();
  }
  else
  {
    e = cursor_->elemento;
  }
}

// Operación privada (auxiliar para IteradorLista<E>::insertar)
// del IteradorLista
template <typename E>
void IteradorLista<E>::insertarDelante(Cursor c)
{
  // Actualización de los punteros al anterior y siguiente de c.
  c->siguiente = cursor_;
  c->anterior  = cursor_->anterior;

  // Actualización del puntero anterior del iterador.
  cursor_->anterior = c;

  // Si el iterador apuntaba al primer elemento de lista_,
  // el nodo insertado pasa a ser el primero de lista_, por
  // lo que hay que actualizar lista_. En otro caso, se actualiza
  // el campo siguiente del nodo anterior a c.
  if (esPrimero())
  {
    lista_.primero_ = c;
  }
  else
  {
    c->anterior->siguiente = c;
  }
}

// Operación privada (auxiliar para IteradorLista<E>::insertar)
// del IteradorLista
template <typename E>
void IteradorLista<E>::insertarDetras(Cursor c)
{
  // Actualización de los punteros al anterior y siguiente de c.
  c->siguiente  = cursor_->siguiente;
  c->anterior  = cursor_;

  // Actualización del puntero anterior del iterador.
  cursor_->siguiente = c;

  // Si el iterador apuntaba al último elemento de lista_,
  // el nodo insertado pasa a ser el último de lista_, por
  // lo que hay que actualizar lista_. En otro caso, se actualiza
  // el campo anterior del nodo posterior a c.
  if (esUltimo())
  {
    lista_.ultimo_ = c;
  }
  else
  {
    c->siguiente->anterior = c;
  }
}

template <typename E>
void IteradorLista<E>::insertar(E e, bool detras)
{
  if (!esIteradorValido())
  {
    lista_.insertarFinal(e);
  }
  else
  {
    Cursor pNodo = lista_.crearNodo(e, nullptr, nullptr);
    if (detras)
    {
      insertarDetras(pNodo);
    }
    else
    {
      insertarDelante(pNodo);
    }
  }
}

template <typename E>
void IteradorLista<E>::reemplazar(E e)
{
  if (!esIteradorValido())
  {
    throw EIteradorNoValido();
  }
  else
  {
    cursor_->elemento = e;
  }
}

template <typename E>
void IteradorLista<E>::eliminar()
{
  if (!esIteradorValido())
  {
    throw EIteradorNoValido();
  }
  else
  {
    Cursor c_aux = cursor_->siguiente;
    if (!esPrimero() && !esUltimo())
    {
      // No es el primero ni el último.
      cursor_->anterior->siguiente = cursor_->siguiente;
      cursor_->siguiente->anterior = cursor_->anterior;
    }
    else
    {
      // Si es el nodo a eliminar es el primero
      if (esPrimero())
      {
        // El primero de la lista será el siguiente
        lista_.primero_ = cursor_->siguiente;

        // Si el siguiente no era nullptr, su campo anterior
        // debe de ser ahora nullptr para marcar el principio
        // de la lista.
        if (cursor_->siguiente != nullptr)
          cursor_->siguiente->anterior = nullptr;
      }

      // Si el nodo a eliminar es el último
      if (esUltimo())
      {
        // El último de la lista será el anterior.
        lista_.ultimo_ = cursor_->anterior;

        // Si el anterior no era nullptr, su campo siguiente
        // debe de ser ahora nullptr para marcar el final
        // de la lista.
        if (cursor_->anterior != nullptr)
          cursor_->anterior->siguiente = nullptr;
      }
    }

    // Destruir el nodo actual.
    delete cursor_;

    // Actualización de cursor_ al siguiente.
    cursor_ = c_aux;
  }
}

template <typename E>
void IteradorLista<E>::siguiente()
{
  if (!esIteradorValido())
  {
    throw EIteradorNoValido();
  }
  else
  {
    cursor_ = cursor_->siguiente;
  }
}

template <typename E>
void IteradorLista<E>::anterior()
{
  if (!esIteradorValido())
  {
    throw EIteradorNoValido();
  }
  else
  {
    cursor_ = cursor_->anterior;
  }
}

template <typename E>
bool IteradorLista<E>::esIteradorValido()
{
  // Mi puntero cursor_ salió de un nodo válido de la lista_
  // (mediante la llamada a lista::primerIterador o lista::ultimoIterador)
  // y se ha modificado el puntero cursor_ únicamente con los métodos
  // de IteradorLista. Entonces la única forma de que sea un puntero
  // no válido (que no apunte a un nodo de lista_) es que apunte a
  // ninguna parte (nullptr en C++11).
  return (cursor_ != nullptr);
}

template <typename E>
bool IteradorLista<E>::esPrimero()
{
  if (esIteradorValido())
  {
    return (lista_.primero_ == cursor_);
  }
  else
  {
    return false;
  }
}

template <typename E>
bool IteradorLista<E>::esUltimo()
{
  if (esIteradorValido())
  {
    return (lista_.ultimo_ == cursor_);
  }
  else
  {
    return false;
  }
}
