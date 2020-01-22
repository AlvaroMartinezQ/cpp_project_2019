/**
 * Modulo: prueba.cpp
 * Tipo: Programa(x) Interfaz-Implementacion TAD ()       Otros()
 * Autor: José Miguel Buenaposada (josemiguel.buenaposada@urjc.es)
 * Fecha: 2019
 * Descripción: programa de prueba de las operaciones sobre Árboles Binarios.
 * Lee la operación a probar de la entrada estándar y escribe el resultado
 * en la salida estándar.
 */

// Descomentar para mandar al Mooshak y Comentar para probar desde fichero
#undef ENTRADA_DESDE_FICHERO

// Descomentar para que el programa de prueba tome la entrada del fichero
// prueba_listas.txt y ¡Comentar para mandar al Mooshak!
// #define ENTRADA_DESDE_FICHERO

#include <iostream>
#ifdef ENTRADA_DESDE_FICHERO
  #include <fstream>
  #include <sstream>
#endif
#include "operaciones_arboles.hpp"
#include "lista.hpp"

#define Elemento int
#define ArbolPrueba ArbolBinario<Elemento>
#define ListaPrueba Lista<Elemento>

void probarNumHijosSoloHijoDchoVacio(std::istream& is)
{
  ArbolPrueba a;
  is >> a;

  std::cout << numNodosSoloHijoDchoVacio(a);
}

void probarRecorridoEnAnchuraIterativo(std::istream& is)
{
  ArbolPrueba a;
  ListaPrueba recorrido;
  is >> a;

  recorridoEnAnchuraIterativo(a, recorrido);

  std::cout << recorrido;
}

void probarElementosNivelK(std::istream& is)
{
  ArbolPrueba a;
  ListaPrueba nivel_k;
  int k;
  is >> k;
  is >> a;

  elementosNivelK(a, k, nivel_k);

  std::cout << nivel_k;
}

void probarEsCompleto(std::istream& is)
{
  ArbolPrueba a;
  is >> a;

  if (esCompleto(a))
  {
    std::cout << "COMPLETO";
  }
  else
  {
    std::cout << "NO COMPLETO";
  }
}

void probarRecorridoEnInordenIterativo(std::istream& is)
{
  ArbolPrueba a;
  ListaPrueba recorrido;

  is >> a;
  recorridoEnInordenIterativo(a, recorrido);

  std::cout << recorrido;
}

void probarReconstruirAB(std::istream& is)
{
  ArbolPrueba a, recons;
  ListaPrueba l_in, l_post;

  is >> a;
  inorden(a, l_in);
  postorden(a, l_post);

  reconstruirAB(l_in, l_post, recons);
  std::cout << recons;
}

int main()
{
  char opcion;

#ifdef ENTRADA_DESDE_FICHERO
  std::ifstream is("prueba_arboles.txt");
  
  if (!is.is_open())
  {
    std::cerr << "No se puede abrir el fichero prueba_arboles.txt" << std::endl;
    return 1;
  }
#else
#define is std::cin
#endif

  try
  {
      // Lectura de la operación a probar
      is >> opcion;

      switch(opcion)
      {
        case 'd': probarNumHijosSoloHijoDchoVacio(is); break;
        case 'a': probarRecorridoEnAnchuraIterativo(is); break;
        case 'k': probarElementosNivelK(is); break;
        case 'c': probarEsCompleto(is); break;
        case 'i': probarRecorridoEnInordenIterativo(is); break;
        case 'r': probarReconstruirAB(is); break;
      }
    }
    catch (std::exception const& excepcion)
    {
      std::cout << "EXCEPCION GENERADA: "  <<  excepcion.what();
    }

#ifdef ENTRADA_DESDE_FICHERO
    // Cerrar el fichero abierto.
    is.close();
#endif

  return 0;
}

