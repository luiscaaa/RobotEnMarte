#ifndef ARBOLQUAD_H
#define ARBOLQUAD_H

#include "NodoQuadtree.h"
#include <list>

template <typename T>
class ArbolQuad {
protected:
    NodoQuadtree<T>* raiz;
public:
    ArbolQuad();
    ~ArbolQuad();
    T obtenerDatoRaiz();
    NodoQuadtree<T>* obtenerRaiz();
    void fijarRaiz(NodoQuadtree<T>* nuevaRaiz);
    bool esVacio();
    bool insertarElemento(T& dato);
    void preOrden(NodoQuadtree<T>* nodo, std::list<T>& lista, int coordX1, int coordX2, int coordY1, int coordY2);
    void elementos_en_rectangulo(int coordX1, int coordX2, int coordY1, int coordY2, T dato, std::list<T>& lista);
    bool insertarElementoRecursivo(NodoQuadtree<T>* nodo, T& dato);
    int obtenerIndiceCuadrante(NodoQuadtree<T>* nodo, T& dato);
};

#include "ArbolQuad.hxx"

#endif



