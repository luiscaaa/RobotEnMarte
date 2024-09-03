#include "Comando_movimiento.h"

Comando_movimiento::Comando_movimiento() {}

Comando_movimiento::Comando_movimiento(int num, std::string tipo, int mag, std::string unidad)
  : numero(num), tipo_movimiento(tipo), magnitud(mag), unidad_medida(unidad) {}

int Comando_movimiento::get_numero() {
  return numero;
}

std::string Comando_movimiento::get_tipo_movimiento() {
  return tipo_movimiento;
}

int Comando_movimiento::get_magnitud() {
  return magnitud;
}

std::string Comando_movimiento::get_unidad_medida() {
  return unidad_medida;
}

void Comando_movimiento::set_numero(int num) {
  this->numero = num;
}

void Comando_movimiento::set_tipo_movimiento(std::string tipo) {
  this->tipo_movimiento = tipo;
}

void Comando_movimiento::set_magnitud(int mag) {
  this->magnitud = mag;
}

void Comando_movimiento::set_unidad_medida(std::string unidad) {
  this->unidad_medida = unidad;
}