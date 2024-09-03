#ifndef NODOQUADTREE_HXX
#define NODOQUADTREE_HXX

#include "NodoQuadtree.h"

template <typename T>
NodoQuadtree<T>::NodoQuadtree() {
    for (int i = 0; i < 4; ++i) {
        hijos[i] = nullptr;
    }
}

template <typename T>
NodoQuadtree<T>::~NodoQuadtree() {
    for (int i = 0; i < 4; ++i) {
        delete hijos[i];
    }
}

template <typename T>
T NodoQuadtree<T>::getDato() {
    return dato;
}

template <typename T>
void NodoQuadtree<T>::setDato(T nuevoDato) {
    this->dato = nuevoDato;
}

template <typename T>
NodoQuadtree<T>* NodoQuadtree<T>::getHijo(int posicion) {
    if (posicion >= 0 && posicion < 4) {
            return hijos[posicion];
    } else {
            return nullptr;
    }
}

template <typename T>
void NodoQuadtree<T>::setHijo(int posicion, NodoQuadtree<T>* nuevoHijo) {
    if (posicion >= 0 && posicion < 4) {
            hijos[posicion] = nuevoHijo;
        }
}

template <typename T>
bool NodoQuadtree<T>::esHoja() {
    for (int i = 0; i < 4; ++i) {
            if (hijos[i] != nullptr) {
                return false;
            }
        }
    return true;
}

#endif