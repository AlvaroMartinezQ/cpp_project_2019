/**
* Modulo: Lista
* Tipo: Programa() Interfaz TAD () Implementacion TAD (X) Otros()
* Autor: José Miguel Buenaposada (josemiguel.buenaposada@urjc.es)
* Fecha: 2015
* Descripción: Implementación de un TAD para representar
*              y manipular Listas de elementos implementada con
*              nodos de doble enlace (parametrizado en
*              función de los elementos que se guardan)
*/

#ifndef nullptr
#define nullptr NULL
#endif

/**
 * POST: Devuelve un único nodo
 *       con elemento 'e', siguiente 'sig' y anterior 'ant'
 */
#include "lista.hpp"

template <typename E>
typename Lista<E>::Nodo*
Lista<E>::crearNodo(E e, Lista<E>::Nodo* ant, Lista<E>::Nodo* sig)
{
  Lista<E>::Nodo* pNodo;

  // new(std::nothrow) permite que pNodo sea nullptr si no hay memoria
  // en lugar de lanzar la excepción std::bad_allow si nos quedamos
  // sin memoria. Lo hacemos así para hacer la traducción de excepciones de
  // std::bad_allow a la que hemos elegido lanzar Lista<E>::EMemoriaAgotada.
  pNodo = new(std::nothrow) Nodo;
  if (!pNodo)
  {
    throw EMemoriaAgotada();
  }
  pNodo->elemento = e;
  pNodo->siguiente = sig;
  pNodo->anterior = ant;

  return pNodo;
}

template <typename E>
void Lista<E>::vaciar()
//  COMPLEJIDAD: O(N), siendo N la longitud de la lista.
{
  Lista<E>::Iterador it = this->primerIterador();
  while (it.esIteradorValido())
  {
    it.eliminar();
  }
}

template <typename E>
Lista<E>::Lista()
{
  primero_ = nullptr;
  ultimo_ = nullptr;
}

template <typename E>
Lista<E>::~Lista()
//  COMPLEJIDAD: O(N), siendo N la longitud de la lista.
{
  vaciar();
}

template <typename E>
void Lista<E>::construir(E e)
//  COMPLEJIDAD: O(1)
{
  // Crear memoria dinámica nueva.
  Nodo* pNodo = crearNodo(e, nullptr, nullptr);

  if (esVacia())
    ultimo_ = pNodo;
  else
  {
    primero_->anterior = pNodo;
    pNodo->siguiente = primero_;
  }

  // Actualizar el puntero al primero nodo de la lista.
  primero_ = pNodo;
}

template <typename E>
void Lista<E>::primero(E& e)
//  COMPLEJIDAD: O(1)
{
  if (esVacia())
    throw EListaVacia();
  else
    e = primero_->elemento;
}

template <typename E>
bool Lista<E>::esVacia()
//  COMPLEJIDAD: O(1)
{
  return (primero_ == nullptr);
}

template <typename E>
int Lista<E>::longitud()
//  COMPLEJIDAD: O(N), donde N es el número de elementos de la lista.
{
  int num_elementos = 0;
  Lista<E>::Iterador it = primerIterador();
  while (it.esIteradorValido())
  {
    num_elementos++;
    it.siguiente();
  }
  return num_elementos;
}

template <typename E>
void Lista<E>::ultimo(E& e)
//  COMPLEJIDAD: O(1)
{
  if (esVacia())
    throw EListaVacia();
  else
    e = ultimo_->elemento;
}

template <typename E>
bool Lista<E>::pertenece(E e)
//  COMPLEJIDAD: O(N), donde N es el número de elementos de la lista.
{
  bool encontrado = false;

  Lista<E>::Iterador it = primerIterador();
  E e_aux;
  while (it.esIteradorValido() && (!encontrado))
  {
    it.obtenerElemento(e_aux);
    encontrado = (e_aux == e);
    it.siguiente();
  }
  return encontrado;
}

template <typename E>
void Lista<E>::resto(Lista& r)
//  COMPLEJIDAD: O(N), donde N es la longitud de la lista.
{
  if (esVacia())
    throw EListaVacia();
  else
  {
    // OJO! Llamamos al operador de asignación de listas (operator =) y
    // este tiene que funcionar para listas en memoria dinámica
    // doblemente enlazadas.
    r = (*this);
    Lista<E>::Iterador it = r.primerIterador(); // Iterador al principio de la lista resto.
    // Elimina el elemento apuntado por it (que es el primero de la lista)
    it.eliminar();
  }
}

template <typename E>
void Lista<E>::insertarFinal(E e)
//  COMPLEJIDAD: O(1)
{
  // Creación del nodo a insertar.
  Nodo* pNodo = crearNodo(e, nullptr, nullptr);

  // Insertar el nodo al final de la lista.
  if (esVacia())
  {
    primero_ = pNodo;
  }
  else
  {
    ultimo_->siguiente = pNodo;
    pNodo->anterior = ultimo_;
  }

  // Actualización del puntero al último nodo
  ultimo_ = pNodo;
}

template <typename E>
void Lista<E>::concatenar(Lista<E> l, Lista<E>& salida)
// COMPLEJIDAD: O(longitud(this) + longitud(l))
//              = O (max (longitud(this), longitud(l)))
{
  if (esVacia())
  {
    salida = l; // Copia directa de la lista 2 (l) sobre la salida.
  }
  else
  {
    Lista<E>* copia_salida = new Lista<E>();
    Lista<E>* copia_l = new Lista<E>();

    (*copia_salida) = (*this); // copiar la lista this en nueva memoria (operator=)
    if (!l.esVacia())
    {
      (*copia_l) = l; // Copiar l con memoria nueva en copia_l (operator=)

      // Conexión de la copia de l (nueva memoria) al final de la
      // lista en la lista actual.
      copia_salida->ultimo_->siguiente = copia_l->primero_;
      copia_l->primero_->anterior = copia_salida->ultimo_;
      copia_salida->ultimo_ = copia_l->ultimo_;
    }

    salida = (*copia_salida);

    delete copia_salida;
    // No hacemos "delete copia_l" porque la memoria de copia_salida
    // la hemos enganchado en copia_salida y eliminando copia_salida
    // liberamos toda la memoria dinámica.
  }
}

template <typename E>
void Lista<E>::borrarElemento(E e)
{
  E e_aux;
  bool encontrado = false;
  Lista<E>::Iterador it = primerIterador();

  // Busqueda del elemento.
  while (it.esIteradorValido() && !encontrado)
  {
    it.obtenerElemento(e_aux);
    if (e_aux == e)
    {
      encontrado = true;
    }
    else
    {
      it.siguiente();
    }
  }

  // Eliminación del nodo cuando se haya encontrado
  // el elemento.
  if (encontrado) // En este caso it.esIteradorValido() es true
  {
    it.eliminar();
  }
}

template<typename E>
Lista<E>& Lista<E>::operator=(Lista& l)
// Operador de asignación
{
  // Sólo se hace la asignación si origen no es this
  if (this != &l)
  {
    if (l.esVacia())
    {
      vaciar();
    }
    else
    {
      // Copiar elementos de l en la lista this.
      Lista<E>::Iterador it_l = l.primerIterador();
      Lista<E>::Iterador it_this = primerIterador();

      while (it_l.esIteradorValido())
      {
        E e;
        it_l.obtenerElemento(e);

        // Actualizar la lista this.
        if (it_this.esIteradorValido())
        {
          it_this.reemplazar(e);
        }
        else
        {
          // Insertar al final de la lista this porque hemos
          // acabado con los nodos que teníamos disponibles
          // en la lista this.
          it_this.insertar(e, true);
        }

        // Pasar a los nodos siguientes de la lista this.
        if (it_this.esIteradorValido())
        {
          it_this.siguiente();
        }

        it_l.siguiente();
      }

      // Liberar la memoria del resto de la lista this
      // (si algún nodo sobraba).
      while (it_this.esIteradorValido())
      {
        it_this.eliminar();
      }
    }
  }

  return (*this);
}

template<typename E>
Lista<E>::Lista(Lista<E>& l)
// Constructor de copia
{
  // Establecemos un valor razonable para los atributos de
  // de un objeto lista que todavía no se ha creado. De esta
  // forma podremos utilizar el operador de asignación para
  // implementar el constructor de copia.
  primero_ = nullptr;
  ultimo_ = nullptr;

  // Utilizamos el operador de asignación sobre nuestro objeto
  // lista que está vacía (¡ni siquiera se ha terminado de
  // crear todavía!).
  (*this) = l;
}

template<typename E>
bool Lista<E>::operator==(Lista& l)
// Operador de comparación: "¿son iguales elemento a elemento?"
{
  E e1, e2;
  Lista<E>::Iterador it1 = primerIterador();
  Lista<E>::Iterador it2 = l.primerIterador();
  bool iguales = true;

  while (it1.esIteradorValido() && it2.esIteradorValido() && iguales)
  {
    it1.obtenerElemento(e1);
    it2.obtenerElemento(e2);

    if (e1 != e2)
    {
      iguales = false;
    }
    else
    {
      it1.siguiente();
      it2.siguiente();
    }
  }

  // Son iguales si las dos listas se han acabado con todos los elementos
  // iguales. Si las listas son iguales pero una de ellas tiene más elementos,
  // entonces no son iguales.
  return (!it1.esIteradorValido() && !it2.esIteradorValido());
}

template<typename E>
bool Lista<E>::operator!=(Lista& l)
{
  return !((*this) == l); // Utilizamos operator==
}
