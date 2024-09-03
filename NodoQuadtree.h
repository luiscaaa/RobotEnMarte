#ifndef NODOQUADTREE_H
#define NODOQUADTREE_H

template <typename T>
class NodoQuadtree {
protected:
    T dato; 
    NodoQuadtree<T>* hijos[4];
public:
    // Constructor
    NodoQuadtree();

    // Destructor
    ~NodoQuadtree();

    T getDato();
    void setDato(T nuevoDato);
    NodoQuadtree<T>* getHijo(int posicion);
    void setHijo(int posicion, NodoQuadtree<T>* nuevoHijo);
    bool esHoja();
};

#include "NodoQuadtree.hxx" 

#endif
