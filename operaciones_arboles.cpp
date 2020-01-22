#include "operaciones_arboles.hpp"

template <typename E>
int numNodosSoloHijoDchoVacio(ArbolBinario<E> a){
    int contador = 0;
    if(!a.esVacio()){
        ArbolBinario<E> miHijoIzquierdo, miHijoDerecho;
        a.hijoDerecho(miHijoDerecho);
        a.hijoIzquierdo(miHijoIzquierdo);
        if(!miHijoDerecho.esVacio() && !miHijoIzquierdo.esVacio()){
            return contador + numNodosSoloHijoDchoVacio(miHijoIzquierdo) + numNodosSoloHijoDchoVacio(miHijoDerecho);
        }else if(!miHijoDerecho.esVacio() && miHijoIzquierdo.esVacio()){
            return contador + numNodosSoloHijoDchoVacio(miHijoDerecho);
        }else if(miHijoDerecho.esVacio() && !miHijoIzquierdo.esVacio()){
            contador++;
            return contador + numNodosSoloHijoDchoVacio(miHijoIzquierdo);
        }else{
            return contador;
        }
    }
    return contador;
}

template <typename E>
void recorridoEnAnchuraIterativo(ArbolBinario<E> a, Lista<E>& recorrido){
    if(a.esVacio()){
        recorrido.vaciar();
    }else{
        Lista<E> miLista;
        E miListaPrimero;
        E miListaUltimo;
        E arbolProfundidad;
        arbolProfundidad = profundidad(a);
        int iteradorProfundidad = 1;
        arbolProfundidad++;
        while(iteradorProfundidad != arbolProfundidad){
            elementosNivelK(a, iteradorProfundidad, miLista);
            miLista.primero(miListaPrimero);
            miLista.ultimo(miListaUltimo);
            while(miListaPrimero != miListaUltimo){
                recorrido.insertarFinal(miListaPrimero);
                miLista.borrarElemento(miListaPrimero);
                miLista.primero(miListaPrimero);
            }
            recorrido.insertarFinal(miListaUltimo);
            iteradorProfundidad++;
            miLista.vaciar();
        }
    }
}

template <typename E>
void elementosNivelK(ArbolBinario<E> a, int k, Lista<E>& nivel_k){
    if(profundidad(a) >= k){
        ArbolBinario<E> miHijoIzquierdo, miHijoDerecho;
        if(k==1){
            E raiz;
            a.raiz(raiz);
            nivel_k.insertarFinal(raiz);
        }else{
            a.hijoDerecho(miHijoDerecho);
            a.hijoIzquierdo(miHijoIzquierdo);
            elementosNivelK(miHijoIzquierdo, k-1, nivel_k);
            elementosNivelK(miHijoDerecho, k-1, nivel_k);
        }
    }
}

template <typename E>
bool esCompleto(ArbolBinario<E> a){
    bool perteneceIzquierda;
    bool perteneceDerecha;
    if(!a.esVacio()){
        ArbolBinario<E> miHijoIzquiero, miHijoDerecho;
        a.hijoIzquierdo(miHijoIzquiero);
        a.hijoDerecho(miHijoDerecho);
        if((miHijoIzquiero.esVacio() && !miHijoDerecho.esVacio()) || (!miHijoIzquiero.esVacio() && miHijoDerecho.esVacio())){
            return false;
        }
        perteneceIzquierda = esCompleto(miHijoIzquiero);
        perteneceDerecha = esCompleto(miHijoDerecho);
        if(perteneceDerecha != perteneceIzquierda){
            return false;
        }
    }
    return true;
}

template <typename E>
void recorridoEnInordenIterativo(ArbolBinario<E> a, Lista<E>& recorrido){
    if(a.esVacio()){
        recorrido.vaciar();
    }else{
        Lista<ArbolBinario<E> > Pila;
        E elementoRaiz;
        ArbolBinario<E> aux;
        aux = a;
        while(!aux.esVacio() || !Pila.esVacia()){
            if(!aux.esVacio()){
                Pila.construir(aux);
                aux.hijoIzquierdo(aux);
            }else{
                Pila.primero(aux);
                Pila.borrarElemento(aux);
                aux.raiz(elementoRaiz);
                recorrido.insertarFinal(elementoRaiz);
                aux.hijoDerecho(aux);
            }
        }
    }
}

template <typename E>
void reconstruirAB(Lista<E> inorden, Lista<E> postorden, ArbolBinario<E>& arbin){
    if(inorden.longitud() != postorden.longitud()){
        throw ERecorridoIncorrecto<E>();
    }else{
        if(!inorden.esVacia() && !postorden.esVacia()){
            E elemento;
            if(inorden.longitud() == 1 && postorden.longitud() == 1){
                postorden.ultimo(elemento);
                ArbolBinario<E> miHijoDerecho, miHijoIzquierdo;
                arbin.construir(miHijoIzquierdo, elemento, miHijoDerecho);
            }else{
                postorden.ultimo(elemento);

                ArbolBinario<E> miHijoDerecho, miHijoIzquierdo;
                Lista<E> listaInordenHI, listaPostordenHI;
                Lista<E> listaInordenHD, listaPostordenHD;
                E elementoObtenidoListaInorden;
                E elementoObtenidoListaPostorden;

                inorden.primero(elementoObtenidoListaInorden);
                postorden.primero(elementoObtenidoListaPostorden);

                while(elementoObtenidoListaInorden != elemento){
                    listaInordenHI.insertarFinal(elementoObtenidoListaInorden);
                    listaPostordenHI.insertarFinal(elementoObtenidoListaPostorden);

                    inorden.borrarElemento(elementoObtenidoListaInorden);
                    postorden.borrarElemento(elementoObtenidoListaPostorden);
                    inorden.primero(elementoObtenidoListaInorden);
                    postorden.primero(elementoObtenidoListaPostorden);
                }
                inorden.borrarElemento(elemento);
                postorden.borrarElemento(elemento);
                listaInordenHD = inorden;
                listaPostordenHD = postorden;
                if(!listaInordenHI.esVacia()){
                    reconstruirAB(listaInordenHI, listaPostordenHI, miHijoIzquierdo);
                }
                if(!listaInordenHD.esVacia()){
                    reconstruirAB(listaInordenHD, listaPostordenHD, miHijoDerecho);
                }
                arbin.construir(miHijoIzquierdo, elemento, miHijoDerecho);
            }
        }
    }
}


template <typename E>
void inorden(ArbolBinario<E> arbin, Lista<E>& lista){
    if(arbin.esVacio()){
        lista.vaciar();
    }else{
        ArbolBinario<E> izqdo, dcho;
        Lista<E> inorden_hi, inorden_hd;
        E r;

        lista.vaciar();

        arbin.hijoIzquierdo(izqdo);
        inorden(izqdo, inorden_hi);

        arbin.hijoDerecho(dcho);
        inorden(dcho, inorden_hd);

        arbin.raiz(r);
        inorden_hd.construir(r);

        inorden_hi.concatenar(inorden_hd, lista);
    }
}

template <typename E>
void postorden(ArbolBinario<E> arbin, Lista<E>& lista){
    if(arbin.esVacio()){
        lista.vaciar();
    }else{
        ArbolBinario<E> izqdo, dcho;
        Lista<E>postorden_hi, postorden_hd;
        E r;

        lista.vaciar();

        arbin.hijoIzquierdo(izqdo);
        postorden(izqdo, postorden_hi);

        arbin.hijoDerecho(dcho);
        postorden(dcho, postorden_hd);

        postorden_hi.concatenar(postorden_hd, lista);

        arbin.raiz(r);
        lista.insertarFinal(r);
    }
}
