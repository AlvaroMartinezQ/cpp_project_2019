/**
* Modulo: ArbolBinarioIO
* Descripción: Implementación de las operaciones de entrada/salida
*              de Árboles Binarios.
*/

#include <iostream>
#include "arbol_binario.hpp"


class EErrorEntrada: public std::runtime_error
{
public:
  EErrorEntrada(const std::string& w = "EErrorEntrada"): std::runtime_error(w) {}
};

template<typename T>
void escribirArbolBinario(std::ostream& os, ArbolBinario<T>& a)
{
  os << "( ";
  if (!a.esVacio())
  {
    T r;
    ArbolBinario<T> izqdo, dcho;
    a.raiz(r);
    os << r << " ";
    a.hijoIzquierdo(izqdo);
    escribirArbolBinario(os,izqdo);
    os << " ";
    a.hijoDerecho(dcho);
    escribirArbolBinario(os,dcho);
  }
  os << " )";
}

/**
 * El formato de E/S establecido para un Árbol de elementos es
 *   () para el arbol binario vacío (solamente)
 *   ( raíz hijo1 hijo2 hijo3 ... ) en otro caso
 *   por ejemplo, ( a ( b ( d () () ) ( e () () ) ) ( c () () ) ).
 *
 *  POST: Se escribe "a" en el stream con el formato especificado
 *        más arriba.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, ArbolBinario<T>& a)
{
  escribirArbolBinario(os, a);
  return os;
}


template<typename T>
void leerArbolBinario(std::istream& is, ArbolBinario<T>& a)
{
  a.vaciar();

  char c;
  bool es_separador = true;
  bool hay_caracteres = true;
  while (hay_caracteres && es_separador)
  {
    is.get(c);
    hay_caracteres = !is.eof();
    es_separador = (c == ' ');
  }

  if (!hay_caracteres || (c != '('))
  {
    throw EErrorEntrada();
  }
  else
  {

    is.get(c);
    hay_caracteres = !is.eof();
    if (c != ')') // Caso base es c == ')'
    {
      T e;
      is >> e;
      ArbolBinario<T> izqdo;
      ArbolBinario<T> dcho;

      leerArbolBinario(is, izqdo);
      leerArbolBinario(is, dcho);

      a.construir(izqdo, e, dcho);

      es_separador = true;
      while (hay_caracteres && es_separador)
      {
        is.get(c);
        hay_caracteres = !is.eof();
        es_separador = (c == ' ');
      }

      if (c != ')')
      {
        throw EErrorEntrada();
      }
    }
  }
}

/**
 * PRE : La entrada por defecto almacena una conjunto "a" con el formato adecuado
 *       Queda espacio en memoria para crear "a"
 * POST: 'c' contendrá el conjunto de de elementos leído
 * EXCEPCIONES: Se activa 'EErrorEntrada' si lo almacenado no tiene la
 *       forma especificada en operator<< o si no queda espacio en memoria
 *       y 'EMemoriaAgotada' si no queda espacio de memoria.
 */
template<typename T>
std::istream& operator>>(std::istream& is, ArbolBinario<T>& a)
{
  leerArbolBinario(is, a);
  return is;
}
