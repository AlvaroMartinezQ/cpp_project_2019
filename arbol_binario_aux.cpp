/**
* Modulo: ArbolBinarioAux
* Tipo: Programa() Interfaz TAD () Implementacion TAD () Otros(X)
* Autor: José Miguel Buenaposada (josemiguel.buenaposada@urjc.es)
* Fecha: 2016
* Descripción: Implementación de subprogramas auxiliares de manejo
*              de Árboles Binarios.
*/

#ifndef nullptr
#define nullptr NULL
#endif

#include <iostream>

template <typename ArbolBin>
int numNodos(ArbolBin arbin)
{
  if (arbin.esVacio())
  {
    return 0;
  }
  else
  {
    ArbolBin izqdo, dcho;
    arbin.hijoIzquierdo(izqdo);
    arbin.hijoDerecho(dcho);
    return 1 + numNodos(izqdo) + numNodos(dcho);
  }
}

template <typename ArbolBin>
int numHojas(ArbolBin arbin)
{
  if (arbin.esVacio())
  {
    return 0;
  }
  else
  {
    ArbolBin izqdo, dcho;
    arbin.hijoIzquierdo(izqdo);
    arbin.hijoDerecho(dcho);

    if (izqdo.esVacio() && dcho.esVacio())
    {
      return 1;
    }
    else
    {
      return numHojas(izqdo) + numHojas(dcho);
    }
  }
}

template <typename ArbolBin>
void espejo(ArbolBin arbin, ArbolBin& imagen)
{
  if (arbin.esVacio())
  {
    imagen.vaciar();
  }
  else
  {
    ArbolBin imagen_izqdo, imagen_dcho;
    typename ArbolBin::Elemento r;

    ArbolBin izqdo, dcho;
    arbin.hijoIzquierdo(izqdo);
    arbin.hijoDerecho(dcho);
    arbin.raiz(r);

    espejo(izqdo, imagen_izqdo);
    espejo(dcho, imagen_dcho);
    imagen.construir(imagen_dcho, r, imagen_izqdo);
  }
}

template <typename ArbolBin>
int profundidad(ArbolBin arbin)
{
  if (arbin.esVacio())
  {
    return 0;
  }
  else
  {
    ArbolBin izqdo, dcho;
    arbin.hijoIzquierdo(izqdo);
    arbin.hijoDerecho(dcho);

    return 1 + std::max(profundidad(izqdo), profundidad(dcho));
  }
}

template <typename ArbolBin>
bool compensado(ArbolBin arbin)
{
  if (arbin.esVacio())
  {
    return true;
  }
  else
  {
    ArbolBin izqdo, dcho;
    arbin.hijoIzquierdo(izqdo);
    arbin.hijoDerecho(dcho);

    return (numNodos(izqdo) == numNodos(dcho));
  }
}

/**
 * POST:
 *  resultado = 0    si eslVacio(arbin)
 *  resultado = 1    si Raiz(arbin)=e
 *  resultado = 1 + minimo (NivelElemento(e, HijoIzqdo(arbin)),
 *                          NivelElemento(e, HijoDcho(arbin)))
 *
 *                       si NivelElemento(e, HijoIzqdo(arbin)) > 0 AND
 *                          NivelElemento(e, HijoDcho(arbin)) > 0
 *
 * resultado = 0    si (NivelElemento(e, HijoIzqdo(arbin)) = 0 AND
 *                      NivelElemento(e, HijoDcho(arbin)) = 0)
 *
 * resultado = 1 + maximo(NivelElemento(e, HijoIzqdo(arbin)),
 *                        NivelElemento(e, HijoDcho(arbin)))
 *                      e.o.c
 */
template <typename ArbolBin>
int nivelElemento(typename ArbolBin::Elemento e, ArbolBin arbin)
{
  if (arbin.esVacio())
  {
    return 0;
  }
  else
  {
    typename ArbolBin::Elemento r;
    arbin.raiz(r);
    if (r == e)
    {
      return 1;
    }
    else
    {
      ArbolBin izqdo, dcho;
      arbin.hijoIzquierdo(izqdo);
      arbin.hijoDerecho(dcho);

      int nivel_izqdo = nivelElemento(e, izqdo);
      int nivel_dcho = nivelElemento(e, dcho);
      if ((nivel_izqdo > 0) && (nivel_dcho > 0))
      {
        return 1 + std::min(nivel_izqdo, nivel_dcho);
      }
      else if ((nivel_izqdo == 0) && (nivel_dcho == 0))
      {
        return 0;
      }
      else
      {
        return 1 + std::max(nivel_izqdo, nivel_dcho);
      }
    }
  }
}

