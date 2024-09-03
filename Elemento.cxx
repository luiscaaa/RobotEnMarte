#include "Elemento.h"

// Constructor por defecto
Elemento::Elemento() {}

// Constructor por parámetros
Elemento::Elemento(int numero, std::string tipo, int tamanio, std::string unidad_medida, int coordX, int coordY) {
    this->numero = numero;
    this->tipo = tipo;
    this->tamanio = tamanio;
    this->unidad_medida = unidad_medida;
    this->coordX = coordX;
    this->coordY = coordY;
}

// Getters y setters

int Elemento::get_numero() {
  return numero;
}

std::string Elemento::get_tipo() {
    return tipo;
}

void Elemento::set_tipo(std::string tipo) {
    this->tipo = tipo;
}

int Elemento::get_tamanio() {
    return tamanio;
}

void Elemento::set_numero(int num) {
  this->numero = num;
}

void Elemento::set_tamanio(int tamanio) {
    this->tamanio = tamanio;
}

std::string Elemento::get_unidad_medida() {
    return unidad_medida;
}

void Elemento::set_unidad_medida(std::string unidad_medida) {
    this->unidad_medida = unidad_medida;
}

int Elemento::get_coordX() {
    return coordX;
}

void Elemento::set_coordX(int coordX) {
    this->coordX = coordX;
}

int Elemento::get_coordY() {
    return coordY;
}

void Elemento::set_coordY(int coordY) {
    this->coordY = coordY;
}
