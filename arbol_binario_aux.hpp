/**
* Modulo: ArbolBinarioAux
* Descripción: Implementación de subprogramas auxiliares de manejo
*              de Árboles Binarios.
*/

#ifndef ARBOL_BINARIO_AUX_HPP
#define ARBOL_BINARIO_AUX_HPP

#include <algorithm>

//namespace ed {

/**
 * POST:
 *  resultado = 0    si esVacio(arbin)
 *  resultado = 1 + numNodos(hijoIzqdo(arbin)) +
 *                  numNodos(hijoDcho(arbin)) e.o.c.
 */
template <typename ArbolBin>
int numNodos(ArbolBin arbin);

/**
 *  POST:
 *  resultado = 0    si esVacio(arbin)
 *  resultado = 1    si esVacio(HijoIzqdo(arbin)) AND EsArbolVacio(HijoDcho(arbin))
 *  resultado = NumHojas(HijoIzqdo(arbin)) + NumHojas(HijoDcho(arbin))  e.o.c. }
 */
template <typename ArbolBin>
int numHojas(ArbolBin arbin);

/**
 * PRE: Queda suficiente espacio en memoria para copiar todos los
 *       elementos de 'arbin' en 'imagen'
 * POST:
 *   CrearArbolVacio(imagen) si esVacio(arbin)
 *   Espejo(HijoIzqdo(arbin), imagen_hi)
 *   Espejo(HijoDcho(arbin), imagen_hd)
 *   Construir(imagen_hd, Raiz(arbin), imagen_hi, imagen) e.o.c.
 * EXCEPCION: 'ArbolBinario::EMemoriaAgotada' si no queda memoria
 */
template <typename ArbolBin>
void espejo(ArbolBin arbin, ArbolBin& imagen);

/**
 * POST:
 *  resultado = 0    si esVacio(arbin)
 *  resultado = 1 +
 *  Maximo(Profundidad(HijoIzqdo(arbin)), Profundidad(HijoDcho(arbin))  e.o.c.
 */
template <typename ArbolBin>
int profundidad(ArbolBin arbin);

/**
 * POST:
 *  resultado = CIERTO si esVacio(arbin)
 *  resultado = NumNodos(HijoIzqdo(arbin))=NumNodos(HijoDcho(arbin)) e.o.c.
 */
template <typename ArbolBin>
bool compensado(ArbolBin arbin);

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
 * resultado = 0    si (NivelElemento(e, HijoIzqdo(arbin)) = 0 ^
 *                      NivelElemento(e, HijoDcho(arbin)) = 0)
 *
 * resultado = 1 + maximo(NivelElemento(e, HijoIzqdo(arbin)),
 *                        NivelElemento(e, HijoDcho(arbin)))
 *                      e.o.c
 */
template <typename ArbolBin>
int nivelElemento(typename ArbolBin::Elemento e, ArbolBin arbin);

#include "arbol_binario_aux.cpp"

//} // namespace ed


#endif
