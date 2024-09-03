#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>

class Elemento {
protected:
    int numero;
    std::string tipo;
    int tamanio;
    std::string unidad_medida;
    int coordX;
    int coordY;

public:
    // Constructor por defecto
    Elemento();

    // Constructor por parámetros
    Elemento(int numero, std::string tipo, int tamanio, std::string unidad_medida, int coordX, int coordY);

    // Getters y setters

    int get_numero();
    void set_numero(int num);

    std::string get_tipo();
    void set_tipo(std::string tipo);

    int get_tamanio();
    void set_tamanio(int tamanio);

    std::string get_unidad_medida();
    void set_unidad_medida(std::string unidad_medida);

    int get_coordX();
    void set_coordX(int coordX);

    int get_coordY();
    void set_coordY(int coordY);
};

#endif // ELEMENTO_H
