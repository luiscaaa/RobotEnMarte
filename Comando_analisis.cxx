#include "Comando_analisis.h"

Comando_analisis::Comando_analisis() {}

Comando_analisis::Comando_analisis(int num, std::string tipo, std::string obj, std::string com)
  : numero(num), tipo_analisis(tipo), objeto(obj), comentario(com), tieneComentario(true) {}

Comando_analisis::Comando_analisis(int num, std::string tipo, std::string obj)
  : numero(num), tipo_analisis(tipo), objeto(obj) {}

int Comando_analisis::get_numero() {
  return numero;
}

std::string Comando_analisis::get_tipo_analisis() {
  return tipo_analisis;
}

std::string Comando_analisis::get_objeto() {
  return objeto;
}

std::string Comando_analisis::get_comentario() {
  return comentario;
}

bool Comando_analisis::get_tieneComentario(){
  return tieneComentario;
}

void Comando_analisis::set_numero(int num) {
  this->numero = num;
}

void Comando_analisis::set_tipo_analisis(std::string tipo) {
  this->tipo_analisis = tipo;
}

void Comando_analisis::set_objeto(std::string obj) {
  this->objeto = obj;
}

void Comando_analisis::set_comentario(std::string com) {
  this->comentario = com;
}

void Comando_analisis::set_tieneComentario(bool tieneCom){
  this->tieneComentario = tieneCom;
}
