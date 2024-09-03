#ifndef _GRAFO_HXX
#define _GRAFO_HXX

#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "Grafo.h"


template<typename V, typename C>
Grafo<V, C>::Grafo() = default;

template<typename V, typename C>
Grafo<V, C>::~Grafo() {
    vertices.clear();
    matrizAdyacencia.clear();
}

template<typename V, typename C>
void Grafo<V, C>::InsertarVertice(const V &vertice) {
    for(int i = 0; i < vertices.size(); i++){
        matrizAdyacencia[i].push_back(std::numeric_limits<C>::max());
    }
    vertices.push_back(vertice);
    std::vector<C> verticeNuevo(vertices.size(), std::numeric_limits<C>::max());
    matrizAdyacencia.push_back(verticeNuevo);
    for (auto& fila : matrizAdyacencia) {
        fila.push_back(std::numeric_limits<C>::max());
    }
}


template<typename V, typename C>
void Grafo<V, C>::InsertarArista(unsigned long origen, unsigned long destino, const C &costo) {
    matrizAdyacencia[origen][destino] = costo;
   // matrizAdyacencia[destino][origen] = costo;
  
}

template<typename V, typename C>
V Grafo<V, C>::ObtenerVertice(unsigned long indice) const {
    return vertices[indice];
}

template<typename V, typename C>
C Grafo<V, C>::ObtenerCosto(unsigned long origen, unsigned long destino) const {
    return matrizAdyacencia[origen][destino];
}

template<typename V, typename C>
unsigned long Grafo<V, C>::NumeroVertices() const {
    return vertices.size();
}

template<typename V, typename C>
std::vector<unsigned long> Grafo<V, C>::Vecinos(unsigned long indice) const {
    std::vector<unsigned long> vecinos;
    for (unsigned long i = 0; i < vertices.size(); ++i) {
        if (matrizAdyacencia[indice][i] != C()) {
            vecinos.push_back(i);
        }
    }
    return vecinos;
}

template<typename V, typename C>
std::vector<V> Grafo<V, C>::ObtenerVertices() const {
    return vertices;
}

 template<typename V, typename C>
typename Grafo<V, C>::TCaminos Grafo<V, C>::Prim(unsigned long inicio) const {
    std::vector<bool> visitado(NumeroVertices(), false);
    visitado[inicio] = true;
    bool entro=false;
    TCaminos caminos(NumeroVertices() - 1);
    std::vector<C> costos(NumeroVertices(), std::numeric_limits<C>::max());

    int valor=0;
    for (unsigned long i = 0; i < NumeroVertices() - 1; ++i) {
        unsigned long minVertice = inicio;
        C minCosto = std::numeric_limits<C>::max();

        for (unsigned long v = 0; v < NumeroVertices(); ++v) {
            if (visitado[v]) {
                for (unsigned long u : Vecinos(v)) {
                    if (!visitado[u] && ObtenerCosto(v, u) < minCosto) {
                        std::cout<<u<<std::endl;
                        minVertice = u;
                        minCosto = ObtenerCosto(v, u);
                        valor=v;
                        entro=true;
                    }
                }
            }
        }

        visitado[minVertice] = true;
        /*
        if (i > 0) {
           // std::cout<<caminos[i-1];
            caminos[i] = caminos[i-1];
        }*/
        if(entro){
        caminos[i].push_back(valor);
        caminos[i].push_back(minVertice);
        entro=false;
        }
    }

    for (auto& ruta : caminos) {
        ruta.insert(ruta.begin(), inicio);
    }
    for (auto& ruta : caminos) {
    if (ruta[0] == inicio) {
        ruta.erase(ruta.begin());
    }
}

    
    return caminos;
}



template<typename V, typename C>
typename Grafo<V, C>::TCaminos Grafo<V, C>::Dijkstra(unsigned long inicio) const
{
    unsigned long numVertices = NumeroVertices();
    if (numVertices <= 1) {
        return TCaminos();
    }

    TCaminos caminos(numVertices);
    std::vector<C> distancias(numVertices, std::numeric_limits<C>::max());
    std::vector<bool> visitado(numVertices, false);

    distancias[inicio] = C();
    caminos[inicio].push_back(inicio); // Agregar origen al inicio de la ruta

    for (unsigned long i = 0; i < numVertices - 1; ++i)
    {
        unsigned long minVertice = 0;
        C minDistancia = std::numeric_limits<C>::max();

        for (unsigned long v = 0; v < numVertices; ++v)
        {
            if (!visitado[v] && distancias[v] < minDistancia)
            {
                minVertice = v;
                minDistancia = distancias[v];
            }
        }

        visitado[minVertice] = true;

        for (unsigned long v = 0; v < numVertices; ++v)
        {
            if (!visitado[v] && matrizAdyacencia[minVertice][v] != C() &&
                distancias[minVertice] + matrizAdyacencia[minVertice][v] < distancias[v])
            {
                distancias[v] = distancias[minVertice] + matrizAdyacencia[minVertice][v];
                caminos[v] = caminos[minVertice];
                caminos[v].push_back(v);
            }
        }
    }

    return caminos;
}

template<typename V, typename C>
std::pair<std::pair<std::vector<V>, std::vector<V>>, C> Grafo<V, C>::EncontrarElementosMasAlejados() {
    // Estructuras de datos auxiliares
    std::vector<C> distancias(NumeroVertices(), std::numeric_limits<C>::max());
    std::vector<unsigned long> padres(NumeroVertices(), std::numeric_limits<unsigned long>::max());

    // Cola de prioridad para el algoritmo de Dijkstra
    std::priority_queue<std::pair<C, unsigned long>, std::vector<std::pair<C, unsigned long>>, std::greater<std::pair<C, unsigned long>>> cola;

    // Inicialización de todos los nodos
    for (unsigned long i = 0; i < NumeroVertices(); ++i) {
        distancias[i] = 0;
        cola.push(std::make_pair(0, i));
    }

    // Bucle principal del algoritmo de Dijkstra
    while (!cola.empty()) {
        unsigned long u = cola.top().second;
        cola.pop();

        for (unsigned long v : Vecinos(u)) {
            C peso = ObtenerCosto(u, v);
            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                padres[v] = u;
                cola.push(std::make_pair(distancias[v], v));
            }
        }
    }

    // Buscar los dos elementos más alejados
    C distanciaMaxima = 0;
    unsigned long elemento1 = 0;
    unsigned long elemento2 = 0;

    for (unsigned long i = 0; i < NumeroVertices(); ++i) {
        if (distancias[i] > distanciaMaxima) {
            distanciaMaxima = distancias[i];
            elemento1 = i;
        }
    }

    distanciaMaxima = 0;
    for (unsigned long i = 0; i < NumeroVertices(); ++i) {
        if (distancias[i] > distanciaMaxima && i != elemento1) {
            distanciaMaxima = distancias[i];
            elemento2 = i;
        }
    }

    // Construir la ruta de los elementos más alejados
    std::vector<unsigned long> ruta1;
    std::vector<unsigned long> ruta2;

    unsigned long elemento = elemento1;
    while (elemento != std::numeric_limits<unsigned long>::max()) {
        ruta1.push_back(elemento);
        elemento = padres[elemento];
    }

    elemento = elemento2;
    while (elemento != std::numeric_limits<unsigned long>::max()) {
        ruta2.push_back(elemento);
        elemento = padres[elemento];
    }

    // Invertir las rutas para que estén en el orden correcto
    std::reverse(ruta1.begin(), ruta1.end());
    std::reverse(ruta2.begin(), ruta2.end());

    // Obtener los elementos correspondientes a las rutas
    std::vector<V> elementosRuta1;
    for (unsigned long indice : ruta1) {
        elementosRuta1.push_back(ObtenerVertice(indice));
    }

    std::vector<V> elementosRuta2;
    for (unsigned long indice : ruta2) {
        elementosRuta2.push_back(ObtenerVertice(indice));
    }

    return std::make_pair(std::make_pair(elementosRuta1, elementosRuta2), distanciaMaxima);
}

#endif // _GRAFO_HXX