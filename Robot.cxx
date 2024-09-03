#include "Robot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

Robot::Robot() {}

Robot::Robot(std::string nombre) : nombre(nombre), direccion(90) {}

std::string Robot::getNombre() {
    return nombre;
}

void Robot::setNombre(std::string nombre) {
    this->nombre = nombre;
}

int Robot::getCoordX() {
        return coordX;
}

int Robot::getCoordY() {
        return coordY;
}

int Robot::getDireccion() {
        return direccion;
}

void Robot::setCoordX(int x) {
        coordX = x;
}

void Robot::setCoordY(int y) {
        coordY = y;
}

void Robot::setDireccion(int dir) {
        direccion = dir;
}

bool Robot::agregar_movimiento(std::string tipo_mov, int magnitud, std::string unidad_med, int& num_aux) {
    if (tipo_mov != "avanzar" && tipo_mov != "girar") {
        std::cout << "La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)." << std::endl;
      return false;
    }
    else if ((tipo_mov == "avanzar" && unidad_med != "unidades") || (tipo_mov == "girar" && unidad_med != "grados") || (tipo_mov == "girar" && (magnitud % 45 != 0))) {
        std::cout << "La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)." << std::endl;
      return false;
    }
    else {
        Comando_movimiento cmd_mov_aux(num_aux, tipo_mov, magnitud, unidad_med);
        q_comandosM.push(cmd_mov_aux);
        num_aux++;
        std::cout << "El comando de movimiento ha sido agregado exitosamente." << std::endl;
      return true;
    }
}

bool Robot::agregar_analisis(std::string tipo_analisis, std::string objeto, std::string comentario, int& num_aux) {
    if (tipo_analisis != "fotografiar" && tipo_analisis != "composicion" && tipo_analisis != "perforar") {
        std::cout << "La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario)" << std::endl;
        return false;
    }
    /*
    // El siguiente if verifica que el comentario esté encerrado en comillas simples
    // "comentario.length() < 2": El comentario debe tener al menos dos caracteres, es decir, debe haber al menos una comilla simple al inicio y al final.
    // "comentario[0] != '\''": El primer caracter del comentario debe ser una comilla simple.
    // "comentario[comentario.length()-1] != '\''": El último caracter del comentario debe ser una comilla simple.
    */
    if (comentario.length() < 2 || comentario[0] != '\'' || comentario[comentario.length()-1] != '\'') {
        std::cout << "La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario)" << std::endl;
        return false;
    }
    //comentario.substr(1, comentario.length()-2)
    Comando_analisis cmd(num_aux, tipo_analisis, objeto, comentario);
    q_comandosA.push(cmd);
    num_aux++;
    std::cout << "El comando de analisis ha sido agregado exitosamente." << std::endl;
    return true;
}

bool Robot::agregar_analisis(std::string tipo_analisis, std::string objeto, int& num_aux) {
    if (tipo_analisis != "fotografiar" && tipo_analisis != "composicion" && tipo_analisis != "perforar") {
        std::cout << "La informacion del analisis no corresponde a los datos esperados (tipo, objeto)" << std::endl;
        return false;
    }
    Comando_analisis cmd(num_aux, tipo_analisis, objeto);
    q_comandosA.push(cmd);
    num_aux++;
    std::cout << "El comando de analisis ha sido agregado exitosamente." << std::endl;
    return true;
}

bool Robot::agregar_elemento(std::string tipo, int tamanio, std::string unidad_med, int coordX, int coordY, int& num_elem) {
    if (tipo != "roca" && tipo != "crater" && tipo != "monticulo" && tipo != "duna") {
        std::cout << "La informacion del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y)." << std::endl;
        return false;
    }
    if (unidad_med != "unidades") {
        std::cout << "La informacion del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y)." << std::endl;
        return false;
    }
    Elemento nuevo_elemento(num_elem, tipo, tamanio, unidad_med, coordX, coordY);
    lista_elementos.push_back(nuevo_elemento);
    num_elem++;
    std::cout << "El elemento ha sido agregado exitosamente." << std::endl;
    return true;
}

void Robot::cargar_comandos(std::string nombre_archivo, int& num_aux) {
    q_comandosM = std::queue<Comando_movimiento>();
    q_comandosA = std::queue<Comando_analisis>();
    bool hayComentario = true;
    std::ifstream archivo(nombre_archivo);
    if (!archivo) {
        std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
        q_comandosM = std::queue<Comando_movimiento>();
        q_comandosA = std::queue<Comando_analisis>();
        archivo.close();
        return;
    }
    
    std::string linea;
    int contador = 0;
    while (std::getline(archivo, linea)) {
        contador++;
        std::istringstream ss(linea);
        std::string tipo;
        ss >> tipo;
        if (tipo == "avanzar" || tipo == "girar") {
            std::string magnitud, unidad_medida;
            ss >> magnitud >> unidad_medida;
            if (!ss || ss.rdbuf()->in_avail() != 0) {
                std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                q_comandosM = std::queue<Comando_movimiento>();
                q_comandosA = std::queue<Comando_analisis>();
                archivo.close();
                return;
            }
            if (!agregar_movimiento(tipo, std::stoi(magnitud), unidad_medida, num_aux)) {
                std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                q_comandosM = std::queue<Comando_movimiento>();
                q_comandosA = std::queue<Comando_analisis>();
                archivo.close();
                return;
            }
        } else if (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar") {
            std::string objeto, comentario;
            ss >> objeto;
            if (!ss) {
                std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                q_comandosM = std::queue<Comando_movimiento>();
                q_comandosA = std::queue<Comando_analisis>();
                archivo.close();
                return;
            }
            if (ss.rdbuf()->in_avail() != 0) {
                ss >> comentario;
                hayComentario = true;
                if (!ss || ss.rdbuf()->in_avail() != 0) {
                    std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                    q_comandosM = std::queue<Comando_movimiento>();
                    q_comandosA = std::queue<Comando_analisis>();
                    archivo.close();
                    return;
                }
            } else {
                hayComentario = false;
                if(!agregar_analisis(tipo, objeto, num_aux)){
                  std::cout << tipo << std::endl << objeto << std::endl << std::endl;
                  std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                q_comandosM = std::queue<Comando_movimiento>();
                q_comandosA = std::queue<Comando_analisis>();
                archivo.close();
                return;
                }
            }
          if(hayComentario){
            if (!agregar_analisis(tipo, objeto, comentario, num_aux)) {
                std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
                q_comandosM = std::queue<Comando_movimiento>();
                q_comandosA = std::queue<Comando_analisis>();
                archivo.close();
                return;
            }
          }
        } else {
            std::cout << nombre_archivo << " no se encuentra o no puede leerse." << std::endl;
            q_comandosM = std::queue<Comando_movimiento>();
            q_comandosA = std::queue<Comando_analisis>();
            archivo.close();
            return;
        }
    }
    archivo.close();
    if (contador == 0) {
        std::cout << nombre_archivo << " no contiene comandos." << std::endl;
    } else {
        std::cout << contador << " comandos cargados correctamente desde " << nombre_archivo << std::endl;
    }
}

void Robot::cargar_elementos(std::string nombre_archivo, int& num_elem) {
    lista_elementos.clear();
    std::ifstream archivo(nombre_archivo);
    if (!archivo) {
        std::cout << nombre_archivo << " no se encuentra o no puede leerse.\n";
        return;
    }

    int contador = 0;
    std::string linea;
    while (std::getline(archivo, linea)) {
      std::istringstream ss(linea);
      std::string tipo, unidad_med;
      int tamanio, coordX, coordY;
      ss >> tipo >> tamanio >> unidad_med >> coordX >> coordY;
        if (!ss || ss.rdbuf()->in_avail() != 0) {
                std::cout << nombre_archivo << " 1no se encuentra o no puede leerse.\n";
                lista_elementos.clear();
                archivo.close();
                return;
        } else{
          if (agregar_elemento(tipo, tamanio, unidad_med, coordX, coordY, num_elem)) {
                contador++;
            }
            else {
                std::cout << nombre_archivo << " no se encuentra o no puede leerse.\n";
                lista_elementos.clear();
                archivo.close();
                return;
            }
        }
    }

    archivo.close();
    if (contador == 0) {
        std::cout << nombre_archivo << " no contiene comandos." << std::endl;
    }else{
        std::cout << contador << " elementos cargados correctamente desde " << nombre_archivo << ".\n";
  }
}

void Robot::guardar(std::string tipo_archivo, std::string nombre_archivo){
    std::ofstream archivo;

    if(tipo_archivo == "comandos"){
      
        if(q_comandosM.empty() && q_comandosA.empty()){
            std::cout<<"La información requerida no está almacenada en memoria"<<std::endl;
            archivo.close();
            return;
        }
      }

      else if(tipo_archivo == "elementos"){

        if(lista_elementos.empty()){
            std::cout<<"La información requerida no está almacenada en memoria"<<std::endl;
            archivo.close();
            return;
        }
        }
  
    archivo.open(nombre_archivo, std::ios::out);
  
    if(!archivo.is_open()){
        std::cout<<"Error guardando en "<<nombre_archivo<<std::endl;
        return;
    }
        
    if(tipo_archivo == "comandos"){
      std::queue<void*> cola_organizada;
      while (!q_comandosM.empty() || !q_comandosA.empty()) {
        if (q_comandosM.empty()) {
            cola_organizada.push(&q_comandosA.front());
            q_comandosA.pop();
        }else if (q_comandosA.empty()) {
            cola_organizada.push(&q_comandosM.front());
            q_comandosM.pop();
        } else {
            Comando_movimiento cm = q_comandosM.front();
            Comando_analisis ca = q_comandosA.front();
            if (comparar_numero(cm, ca)) {
                cola_organizada.push(&q_comandosM.front());
                q_comandosM.pop();
            }else {
                cola_organizada.push(&q_comandosA.front());
                q_comandosA.pop();
            }
          }
      }

      void* elemento = cola_organizada.front();
        cola_organizada.pop();

        Comando_movimiento* cm = static_cast<Comando_movimiento*>(elemento);
          if(cm->get_tipo_movimiento() == "avanzar" || cm->get_tipo_movimiento() == "girar"){
             archivo << cm->get_tipo_movimiento() << " " << cm->get_magnitud() << " " << cm->get_unidad_medida();
          }else{
            Comando_analisis* ca = static_cast<Comando_analisis*>(elemento);
          if(ca->get_tieneComentario()){
            archivo << ca->get_tipo_analisis() << " " << ca->get_objeto() << " " << ca->get_comentario();
          }else{
            archivo << ca->get_tipo_analisis() << " " << ca->get_objeto();
          }
          }

      while (!cola_organizada.empty()) {
        void* elemento = cola_organizada.front();
        cola_organizada.pop();

          Comando_movimiento* cm = static_cast<Comando_movimiento*>(elemento);
          if(cm->get_tipo_movimiento() == "avanzar" || cm->get_tipo_movimiento() == "girar"){
             archivo << std::endl << cm->get_tipo_movimiento() << " " << cm->get_magnitud() << " " << cm->get_unidad_medida();
          }else{
            Comando_analisis* ca = static_cast<Comando_analisis*>(elemento);
          if(ca->get_tieneComentario()){
            archivo << std::endl << ca->get_tipo_analisis() << " " << ca->get_objeto() << " " << ca->get_comentario();
          }else{
            archivo << std::endl << ca->get_tipo_analisis() << " " << ca->get_objeto();
          }
          } 
      }
    }else if(tipo_archivo == "elementos"){
      std::list<Elemento>::iterator it;

        for (it = lista_elementos.begin(); it != std::prev(lista_elementos.end()); it++) {
            archivo << it->get_tipo() << " " << it->get_tamanio() << " " << it->get_unidad_medida() << " " << it->get_coordX() << " " << it->get_coordY() << std::endl;
        }
      it= std::prev(lista_elementos.end());
      archivo << it->get_tipo() << " " << it->get_tamanio() << " " << it->get_unidad_medida() << " " << it->get_coordX() << " " << it->get_coordY();
    }

    else{
        std::cout<<"Error guardando en "<<nombre_archivo<<std::endl;
        archivo.close();
        return;
    }

    archivo.close();
    std::cout<<"La información ha sido guardada en "<<nombre_archivo<<std::endl;
}



void Robot::mostrar_comandos_movimiento(){
  std::queue<Comando_movimiento> q_aux;
   while (!q_comandosM.empty()) {
    Comando_movimiento cmd = q_comandosM.front();
    std::cout << "Tipo de movimiento: " << cmd.get_tipo_movimiento() << ", magnitud: " << cmd.get_magnitud() << ", unidad de medida: " << cmd.get_unidad_medida() << std::endl;
     q_aux.push(cmd);
    q_comandosM.pop();
}
  while(!q_aux.empty()){
    q_comandosM.push(q_aux.front());
    q_aux.pop();
  }
}

void Robot::mostrar_comandos_analisis(){
  std::queue<Comando_analisis> q_aux;
   while (!q_comandosA.empty()) {
    Comando_analisis cmd = q_comandosA.front();
    std::cout << "Tipo de analisis: " << cmd.get_tipo_analisis() << ", objeto: " << cmd.get_objeto() << ", comentario: " << cmd.get_comentario() << std::endl;
     q_aux.push(cmd);
    q_comandosA.pop();
}
  while(!q_aux.empty()){
    q_comandosA.push(q_aux.front());
    q_aux.pop();
  }
}

void Robot::mostrar_elementos(){
  std::list<Elemento>::iterator it;
  for(it = lista_elementos.begin(); it != lista_elementos.end(); it++){
    std::cout << "Tipo elemento: " << it->get_tipo() << ", tamaño: " << it->get_tamanio() << ", unidad medida: " << it->get_unidad_medida() << ", coordenada X: " << it->get_coordX() << ", coordenada Y: " << it->get_coordY() << ", numero: " << it->get_numero()+1 << std::endl;
  }
}

void Robot::simular_comandos(int X, int Y){
  std::queue<Comando_movimiento> q_aux;
  this->setDireccion(0);
  this->setCoordX(X);
  this->setCoordY(Y);

  if(q_comandosM.empty()){
    std::cout << "La informacion requerida no esta almacenada en memoria." << std::endl;
    return;
  }

  while(!q_comandosM.empty()){
    int dir_aux = 0;
    Comando_movimiento cm = q_comandosM.front();
    if(cm.get_tipo_movimiento() == "girar"){
      if(cm.get_magnitud() >= 0){
        dir_aux = (this->getDireccion() + cm.get_magnitud()) % 360;
      } else{
        dir_aux = (this->getDireccion() - cm.get_magnitud() + 360) % 360;
      }
      this->setDireccion(dir_aux);
      std::cout << "Comando realizado con exito" << std::endl;
    }else if(cm.get_tipo_movimiento() == "avanzar"){
      int x_aux = this->getCoordX();
      int y_aux = this->getCoordY();

      if (this->getDireccion() == 0) {
        x_aux += cm.get_magnitud();  // mover hacia la derecha
      } else if (this->getDireccion() == 45) {
        x_aux += cm.get_magnitud();  // mover hacia la derecha
        y_aux += cm.get_magnitud();  // mover hacia arriba
      } else if (this->getDireccion() == 90) {
        y_aux += cm.get_magnitud();  // mover hacia arriba
      } else if (this->getDireccion() == 135) {
        x_aux -= cm.get_magnitud();  // mover hacia la izquierda
        y_aux += cm.get_magnitud();  // mover hacia arriba
      } else if (this->getDireccion() == 180) {
        x_aux -= cm.get_magnitud();  // mover hacia la izquierda
      } else if (this->getDireccion() == 225) {
        x_aux -= cm.get_magnitud();  // mover hacia la izquierda
        y_aux -= cm.get_magnitud();  // mover hacia abajo
      } else if (this->getDireccion() == 270) {
        y_aux -= cm.get_magnitud();  // mover hacia abajo
      } else if (this->getDireccion() == 315) {
        x_aux += cm.get_magnitud();  // mover hacia la derecha
        y_aux -= cm.get_magnitud();  // mover hacia abajo
      }

      for(Elemento elemento : lista_elementos){
        if(x_aux >= elemento.get_coordX() && x_aux <= elemento.get_coordX() + elemento.get_tamanio() && y_aux >= elemento.get_coordY() && y_aux <= elemento.get_coordY() + elemento.get_tamanio()){
          std::cout << "Los comandos no pudieron ser simulados porque un elemento interfiere con el movimiento." << std::endl;
          q_aux.push(cm);
          q_comandosM.pop();
          while(!q_aux.empty()){
          q_comandosM.push(q_aux.front());
          q_aux.pop();
          }
          return;
        }
      }
      this->setCoordX(x_aux);
      this->setCoordY(y_aux);
      std::cout << "Comando realizado con exito" << std::endl;
    }
    q_aux.push(cm);
    q_comandosM.pop();
  }
  std::cout << "La simulación de los comandos, a partir de la posicion (" << X << ", " << Y << "), deja al robot en la nueva posición (" << this->getCoordX() << ", " << this->getCoordY() << ")." << std::endl;

  while(!q_aux.empty()){
    q_comandosM.push(q_aux.front());
    q_aux.pop();
    }
}

bool Robot::comparar_numero(Comando_movimiento& cm, Comando_analisis& ca) {
    return cm.get_numero() < ca.get_numero();
}

void Robot::crear_mapa(float coeficiente_conectividad, TGraph& grafo){

  if (lista_elementos.empty()) {
            std::cout << "La información requerida no está almacenada en memoria." << std::endl;
            return;
  }

  std::list<Elemento>::iterator it;
  for( it = lista_elementos.begin(); it != lista_elementos.end(); it++ )
  {
    grafo.InsertarVertice( *it );
  } 

  int num_vecinos = std::floor(lista_elementos.size() * coeficiente_conectividad);
  //std::cout << "Numero de vecinos: " << num_vecinos << std::endl;
  float dist = 0;

  for (auto it = lista_elementos.begin(); it != lista_elementos.end(); it++) {
        std::vector<std::pair<float, int>> distances;
        for (auto it2 = lista_elementos.begin(); it2 != lista_elementos.end(); it2++) {
            if (it != it2) {
                dist = distanceTo(it->get_coordX(), it->get_coordY(), it2->get_coordX(), it2->get_coordY());
                distances.push_back(std::make_pair(dist, it2->get_numero()));
            }
        }

    std::sort(distances.begin(), distances.end());

    for (int k = 0; k < num_vecinos; k++) {
            grafo.InsertarArista((it->get_numero()), (distances[k].second), (distances[k].first));
        }
  }

  std::cout << "El mapa se ha creado exitosamente. Cada elemento tiene " << num_vecinos << " vecinos." << std::endl;
  
return;
}

void Robot::ruta_mas_larga(TGraph& grafo){

  unsigned long numVertices = grafo.NumeroVertices();

  if(numVertices == 0){
    std::cout << "El mapa no ha sido generado todavía (con el comando crear_mapa)." << std::endl;
    return;
  }
  
  std::pair<std::pair<std::vector<Elemento>, std::vector<Elemento>>, float> elementosMasAlejados = grafo.EncontrarElementosMasAlejados();
    std::vector<Elemento> ruta1 = elementosMasAlejados.first.first;
    std::vector<Elemento> ruta2 = elementosMasAlejados.first.second;
    float distancia = elementosMasAlejados.second;

    std::cout << "Los puntos de interes mas alejados entre si son " << ruta1[0].get_tipo() << " y " << ruta1[ruta1.size()-1].get_tipo() << ". La ruta que los conecta tiene una longitud total de " << distancia << " y pasa por los siguientes elementos: " << std::endl;
  
    for (Elemento vertice : ruta1) {
        std::cout << vertice.get_tipo() << " " << vertice.get_tamanio() << " " << vertice.get_unidad_medida() << " " << vertice.get_coordX() << " " << vertice.get_coordY();
    }
    std::cout << std::endl;

    /*for (Elemento vertice : ruta2) {
        std::cout << vertice.get_tipo() << " ";
    }
    std::cout << std::endl;*/

    //std::cout << "Distancia: " << distancia << std::endl;

    return;  
}

int Robot::distanceTo(int coordX1, int coordY1, int coordX2, int coordY2) {
        int dx = coordX2 - coordX1;
        int dy = coordY2 - coordY1;
        return std::sqrt(dx*dx + dy*dy);
}

void Robot::ubicar_elementos(TArbol& arbol) {
    if (lista_elementos.empty()) {
        std::cout << "La información requerida no está almacenada en memoria" << std::endl;
        return;
    }

    std::list<Elemento>::iterator it;
    std::vector<Elemento> elementos_no_procesados;

    for (it = lista_elementos.begin(); it != lista_elementos.end(); it++) {
        //arbol.insertarElemento(*it);
        if (!arbol.insertarElemento(*it)) {
            elementos_no_procesados.push_back(*it);
        }
    }

    if (!elementos_no_procesados.empty()) {
        std::cout << "Los siguientes elementos no pudieron procesarse adecuadamente: ";
        for (auto& elemento : elementos_no_procesados) {
            std::cout << "Tipo elemento: " << elemento.get_tipo() << ", tamaño: " << elemento.get_tamanio() << ", unidad medida: " << elemento.get_unidad_medida() << ", coordenada X: " << elemento.get_coordX() << ", coordenada Y: " << elemento.get_coordY() << std::endl;
        }
        std::cout << std::endl;
    }
}

void Robot::en_cuadrante(int coordX1, int coordX2, int coordY1, int coordY2, TArbol& arbol) {
    std::list<Elemento> lista_en_cuadrante;
  
    if (coordX1 >= coordX2 || coordY1 >= coordY2) {
        std::cout << "La información del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)." << std::endl;
        return;
    }
    
    if (arbol.esVacio()) {
        std::cout << "Los elementos no han sido ubicados todavía (con el comando ubicar_elementos)." << std::endl;
        return;
    }
    
    arbol.preOrden(arbol.obtenerRaiz(), lista_en_cuadrante, coordX1, coordX2, coordY1, coordY2);

    std::cout << "Los elementos ubicados en el cuadrante solicitado son: " << std::endl;

    std::list<Elemento>::iterator it;
    for(it = lista_en_cuadrante.begin(); it != lista_en_cuadrante.end(); it++){
      std::cout << "Tipo elemento: " << it->get_tipo() << ", tamaño: " << it->get_tamanio() << ", unidad medida: " << it->get_unidad_medida() << ", coordenada X: " << it->get_coordX() << ", coordenada Y: " << it->get_coordY() << std::endl;
    }
}