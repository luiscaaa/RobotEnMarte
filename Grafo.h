#ifndef _GRAFO_H
#define _GRAFO_H

#include <vector>    

template<typename V, typename C>

class Grafo {
public:
    
    Grafo();
    ~Grafo();

    void InsertarVertice(const V &vertice);

    void InsertarArista(unsigned long origen, unsigned long destino, const C &costo);

    V ObtenerVertice(unsigned long indice) const;

    C ObtenerCosto(unsigned long origen, unsigned long destino) const;

    unsigned long NumeroVertices() const;

    std::vector<unsigned long> Vecinos(unsigned long indice) const;

    std::vector<V> ObtenerVertices() const;


    typedef std::vector<std::vector<unsigned long>> TCaminos;
    TCaminos Prim(unsigned long inicio) const;
    TCaminos Dijkstra(unsigned long inicio) const;

    std::pair<std::pair<std::vector<V>, std::vector<V>>, C> EncontrarElementosMasAlejados();

    std::vector<V> vertices;
    std::vector<std::vector<C>> matrizAdyacencia;
};

#include "Grafo.hxx"

#endif //_GRAFO_H