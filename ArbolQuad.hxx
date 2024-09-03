#ifndef ARBOLQUAD_HXX
#define ARBOLQUAD_HXX

#include "ArbolQuad.h"
#include <stdexcept>
#include <iostream>

template <typename T>
ArbolQuad<T>::ArbolQuad() {
    raiz = nullptr;
}

template <typename T>
ArbolQuad<T>::~ArbolQuad() {
    if (raiz != nullptr) {
            delete raiz;
        }
}

template <typename T>
T ArbolQuad<T>::obtenerDatoRaiz() {
    if (raiz != nullptr) {
        return raiz->getDato();
    } else {
        throw std::runtime_error("El árbol está vacío. No se puede obtener el dato de la raíz.");
    }
}

template <typename T>
NodoQuadtree<T>* ArbolQuad<T>::obtenerRaiz() {
    return raiz;
}

template <typename T>
void ArbolQuad<T>::fijarRaiz(NodoQuadtree<T>* nuevaRaiz) {
    this->raiz = nuevaRaiz;
}

template <typename T>
bool ArbolQuad<T>::esVacio() {
    return (raiz == nullptr);
}

template <typename T>
bool ArbolQuad<T>::insertarElemento(T& dato) {
    if (raiz == nullptr) {
            raiz = new NodoQuadtree<T>();
            raiz->setDato(dato);
        } else {
            insertarElementoRecursivo(raiz, dato);
        }
  return true;
}

template <typename T>
bool ArbolQuad<T>::insertarElementoRecursivo(NodoQuadtree<T>* nodo, T& dato) {
        int indiceCuadrante = obtenerIndiceCuadrante(nodo, dato);

        // Verificar si el hijo correspondiente está vacío
        if (nodo->getHijo(indiceCuadrante) == nullptr) {
            // El hijo correspondiente está vacío, crearemos un nuevo nodo y lo estableceremos como hijo
            NodoQuadtree<T>* nuevoHijo = new NodoQuadtree<T>();
            nuevoHijo->setDato(dato);
            nodo->setHijo(indiceCuadrante, nuevoHijo);
        } else {
            // El hijo correspondiente no está vacío, continuamos descendiendo en el árbol
            insertarElementoRecursivo(nodo->getHijo(indiceCuadrante), dato);
        }
  return true;
}

template <typename T>
int ArbolQuad<T>::obtenerIndiceCuadrante(NodoQuadtree<T>* nodo, T& dato) {
    //Obtener las coordenadas del nodo y del dato
    int nodoX = nodo->getDato().get_coordX();
    int nodoY = nodo->getDato().get_coordY();
    int datoX = dato.get_coordX();
    int datoY = dato.get_coordY();

    // Comparar las coordenadas y determinar el índice del cuadrante correspondiente
    if (datoX <= nodoX && datoY <= nodoY) {
        return 3;  // Menor o igual en X y menor o igual en Y
    } else if (datoX <= nodoX && datoY > nodoY) {
        return 0;  // Menor o igual en X pero mayor en Y
    } else if (datoX > nodoX && datoY <= nodoY) {
        return 2;  // Mayor en X pero menor o igual en Y
    } else {
        return 1;  // Mayor en X y mayor en Y
    }
}

template <typename T>
void ArbolQuad<T>::preOrden(NodoQuadtree<T>* nodo, std::list<T>& lista, int coordX1, int coordX2, int coordY1, int coordY2) {
    if (nodo != nullptr) {
            elementos_en_rectangulo(coordX1, coordX2, coordY1, coordY2, nodo->getDato(), lista);
            //std::cout << nodo->getDato().get_tipo() << " ";
      
            // Recorrer los hijos en preorden
            for (int i = 0; i < 4; i++) {
                preOrden(nodo->getHijo(i), lista, coordX1, coordX2, coordY1, coordY2);
            }
        }
}

template <typename T>
void ArbolQuad<T>::elementos_en_rectangulo(int coordX1, int coordX2, int coordY1, int coordY2, T dato, std::list<T>& lista) {

    int datoX = dato.get_coordX(); 
    int datoY = dato.get_coordY(); 

    if (datoX >= coordX1 && datoX <= coordX2 && datoY >= coordY1 && datoY <= coordY2) {
        lista.push_back(dato);
    }

}

#endif







