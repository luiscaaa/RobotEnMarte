#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <queue>
#include <list>
#include "Comando_movimiento.h"
#include "Comando_analisis.h"
#include "Elemento.h"
#include "Grafo.h"
#include "ArbolQuad.h"

class Robot {
private:
    std::string nombre;
    int coordX;
    int coordY;
    int direccion;
    std::queue<Comando_movimiento> q_comandosM;
    std::queue<Comando_analisis> q_comandosA;
    std::list<Elemento> lista_elementos;

public:
    // Constructor por defecto
    Robot();

    // Constructor por parámetros
    Robot(std::string nombre);

    // Getters y setters
    std::string getNombre();
    void setNombre(std::string nombre);
    int getCoordX();
    void setCoordX(int x);
    int getCoordY();
    void setCoordY(int y);
    int getDireccion();
    void setDireccion(int dir);

    // Método para agregar un comando de movimiento a la cola
    bool agregar_movimiento(std::string tipo_mov, int magnitud, std::string unidad_med, int& num_aux);

    // Método para agregar un comando de análisis a la cola
    bool agregar_analisis(std::string tipo_analisis, std::string objeto, std::string comentario, int& num_aux);
    bool agregar_analisis(std::string tipo_analisis, std::string objeto, int& num_aux);

    // Método para agregar un elemento a la lista
    bool agregar_elemento(std::string tipo, int tamanio, std::string unidad_med, int coordX, int coordY, int& num_elem);

    // Método para cargar los comandos de desplazamiento
    void cargar_comandos(std::string nombre_archivo, int& num_aux);

    // Método para cargar los elementos
    void cargar_elementos(std::string nombre_archivo, int& num_elem);

    // Mostrar los comandos en la cola de comandos de movimiento
    void mostrar_comandos_movimiento();

    // Mostrar los comandos en la cola de comandos de analisis
    void mostrar_comandos_analisis();

    // Mostrar los elementos en la lista de elementos
    void mostrar_elementos();

    // Método para guardar la información
    void guardar(std::string tipo_archivo, std::string nombre_archivo);

    //Método para simular los comandos
    void simular_comandos(int coordX, int coordY);

    //Método para comparar el numero de cada comando
    bool comparar_numero(Comando_movimiento& cm, Comando_analisis& ca);

    //Método para ubicar elementos
    typedef ArbolQuad<Elemento> TArbol;
    void ubicar_elementos(TArbol& arbol);

    //Método para encontrar los elementos dentro del cuadrante
    void en_cuadrante(int coordX1, int coordX2, int coordY1, int coordY2, TArbol& arbol);

    //Método para crear el mapa
    typedef Grafo< Elemento, float > TGraph;
    void crear_mapa(float coeficiente_conectividad, TGraph& grafo);

    //Método para encontrar la ruta más larga
    void ruta_mas_larga(TGraph& grafo);

    //Método para calcular distancia euclidiana
    int distanceTo(int coordX1, int coordY1, int coordX2, int coordY2);
};

#endif // ROBOT_H
