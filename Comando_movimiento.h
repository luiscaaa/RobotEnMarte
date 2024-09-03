#ifndef COMANDO_MOVIMIENTO_H
#define COMANDO_MOVIMIENTO_H

#include <string>

class Comando_movimiento {
  protected:
    int numero;
    std::string tipo_movimiento;
    int magnitud;
    std::string unidad_medida;

  public:
    Comando_movimiento();
    Comando_movimiento(int numero, std::string tipo, int mag, std::string unidad);
    int get_numero();
    std::string get_tipo_movimiento();
    int get_magnitud();
    std::string get_unidad_medida();
    void set_numero(int num);
    void set_tipo_movimiento(std::string tipo);
    void set_magnitud(int mag);
    void set_unidad_medida(std::string unidad);
};

#endif // COMANDO_MOVIMIENTO_H