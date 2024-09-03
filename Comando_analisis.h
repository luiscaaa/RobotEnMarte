#ifndef COMANDO_ANALISIS_H
#define COMANDO_ANALISIS_H

#include <string>

class Comando_analisis {
  protected:
    int numero;
    std::string tipo_analisis;
    std::string objeto;
    std::string comentario;
    bool tieneComentario = false;

  public:
    Comando_analisis();
    Comando_analisis(int numero, std::string tipo, std::string obj, std::string com);
    Comando_analisis(int numero, std::string tipo, std::string obj);
    int get_numero();
    std::string get_tipo_analisis();
    std::string get_objeto();
    std::string get_comentario();
    bool get_tieneComentario();
    void set_numero(int num);
    void set_tipo_analisis(std::string tipo);
    void set_objeto(std::string obj);
    void set_comentario(std::string com);
    void set_tieneComentario(bool tieneCom);
};

#endif // COMANDO_ANALISIS_H
