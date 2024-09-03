#include "Robot.h"
#include "Grafo.h"
#include "ArbolQuad.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

vector<string> separar_palabras(string frase) {
  vector<string> words;
  stringstream ss(frase);
  string word;

  while (ss >> word) {
    words.push_back(word);
  }
    return words;
}

string lowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

std::ostream& operator<<(std::ostream& os, Elemento& elemento) {
    os << elemento.get_tipo(); // Imprime el tipo de elemento o cualquier otro dato deseado
    return os;
}

typedef Grafo< Elemento, float > TGraph;
typedef ArbolQuad< Elemento > TArbol;

bool validarComando(vector<string> comando, Robot& robot, int& num_aux, int& num_elem, TArbol& arbol, TGraph& g) {

    //Ayuda para el comando de ayuda especifico para cada comando
    if (comando[0] == "ayuda" && comando.size() == 2)
    {
      if (comando [1] == "cargar_comandos")
      {
        cout<<"Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los comandos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de comandos (usando el comando cargar_comandos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de comandos de diferentes archivos."<<endl;
        return true;
      }
      else if( comando[1] == "cargar_elementos")
      {
        cout<<"Carga en memoria los datos de puntos de interés o elementos contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los elementos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de puntos de interés (usando el comando cargar_elementos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes archivos."<<endl;
        return true;
      }
      else if( comando[1] == "agregar_movimiento")
      {
        cout<<"Agrega el comando de movimiento descrito a la lista de comandos del robot “Curios- ity”. El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida corresponde a la convención con la que se mide la magnitud del movimiento (centimetros, metros, grados, ...). Si no se envía la información completa y adecuada del comando de movimiento, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
        return true;
      }
      else if( comando[1] == "agregar_analisis")
      {
        cout<<"Agrega el comando de análisis descrito a la lista de comandos del robot “Curiosity”. El análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar más información sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples (ejemplo: ’roca_cuadrante_32’). Si no se envía la información completa y adecuada del comando de análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
        return true;
      }
      else if( comando[1] == "agregar_elemento")
      {
        cout<<"Agrega el componente o elemento descrito a la lista de puntos de interés del robot “Cu- riosity”. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa este valor con la convención que se usó para su medición (centimetros, metros, ...). Finalmente, las coordenadas x y y corresponden a números reales que permiten conocer la ubicación del elemento en el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la información completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés que se enviarán al robot desde la tierra."<<endl;
        return true;
      }
      else if( comando[1] == "guardar")
      {
        cout<<"Guarda en el archivo nombre_archivo la información solicitada de acuerdo al tipo de archivo: comandos almacena en el archivo la información de comandos de movimiento y de análisis que debe ejecutar el robot, elementos almacena en el archivo la información de los componentes o puntos de interés conocidos en el suelo marciano."<<endl;
        return true;
      }
      else if( comando[1] == "simular_comandos")
      {
        cout<<"Permite simular el resultado de los comandos de movimiento que se enviarán al robot “Curiosity” desde la Tierra, facilitando asi la validación de la nueva posición en la que podría ubicarse. Para ejecutarse adecuadamente, requiere conocer la posición actual (coordenadas x y y) del vehículo. Hay que tener en cuenta que sólo los comandos de movimiento son necesarios, no los de análisis."<<endl;
        return true;
      }
      else if( comando[1] == "salir")
      {
        cout<<"Termina la ejecución de la aplicación."<<endl;
        return true;
      }
      else if( comando[1] == "ubicar_elementos")
      {
        cout<<"El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura de datos jerárquica adecuada, que permita luego realizar consultas geográficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error, pero deben terminarse de procesar todos los elementos almacenados en memoria."<<endl;
        return true;
      }
      else if( comando[1] == "en_cuadrante")
      {
        cout<<"Permite utilizar la estructura creada con el comando anterior para retornar una lista de los componentes o elementos que están dentro del cuadrante geográfico descrito por los límites de coordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar la búsqueda por cuadrantes. Los límites de coordenadas deben garantizar que coordX1<coordX2 y coordY1<coordY2."<<endl;
        return true;
      }
      else if( comando[1] == "crear_mapa")
      {
        cout<<"El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura no lineal y conectarlos entre sí teniendo en cuenta el coeficiente de conec- tividad dado. El objetivo es que cada elemento esté conectado a los demás elementos más cercanos a él, midiendo la cercanía a través de la distancia euclidiana entre los elementos. Esta distancia euclidiana también se utiliza como el peso o etiqueta de la conexión entre los elementos. Con el coeficiente de conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicarán en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14)."<<endl;
        return true;
      }
      else if( comando[1] == "ruta_mas_larga")
      {
        cout<<"Con el mapa ya creado, el comando permite identificar los dos componentes más alejados entre sí de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los ele- mentos más alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que estén a mayor distancia euclidiana entre sí. Al encontrar esa ruta más larga dentro del mapa, el comando imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir para ir del elemento origen al elemento destino."<<endl;
        return true;
      }
      else {return false;}   
    }

  // COMANDO QUE RECIBE LOS PARAMETROS DE CADA METODO
  else if (comando[0]=="cargar_comandos" && comando.size()== 2 ){
        robot.cargar_comandos(comando[1], num_aux);
        //robot.mostrar_comandos_movimiento();
        //robot.mostrar_comandos_analisis();
        return true;
      }
  else if (comando[0]=="cargar_elementos" && comando.size()== 2 ){
        robot.cargar_elementos(comando[1], num_elem);
        //robot.mostrar_elementos();
        return true;
      }
  else if (comando[0]=="agregar_movimiento" && comando.size()== 4 ){
        robot.agregar_movimiento(comando[1], stoi(comando[2]), comando[3], num_aux);
        //robot.mostrar_comandos_movimiento();
        return true;
      }
  else if (comando[0]=="agregar_analisis" && (comando.size()== 3 || comando.size()==4)){
        if(comando.size()==3){
          robot.agregar_analisis(comando[1], comando[2], num_aux);
        }else{
          robot.agregar_analisis(comando[1], comando[2], comando[3], num_aux);
        }
        //robot.mostrar_comandos_analisis();
        return true;
      }
  else if (comando[0]=="agregar_elemento" && comando.size()== 6 ){
        robot.agregar_elemento(comando[1], stoi(comando[2]), comando[3], stoi(comando[4]), stoi(comando[5]), num_elem);
        //robot.mostrar_elementos();
        return true;
      }
  else if (comando[0]=="guardar" && comando.size()== 3 ){
        robot.guardar(comando[1], comando[2]);
        return true;
      }
  else if (comando[0]=="simular_comandos" && comando.size()== 3 ){
        robot.simular_comandos(stoi(comando[1]), stoi(comando[2]));
        return true;
      }
  else if (comando[0]=="salir" && comando.size()== 1 ){
        return true;
      }
  else if (comando[0]=="ubicar_elementos" && comando.size()== 1 ){
        robot.ubicar_elementos(arbol);
        if(!arbol.esVacio()){
          cout << "Los elementos han sido procesados exitosamente." << endl;
        }/*else{
          cout << "Vacio" << endl;
        }

       
      try {
     cout << "Dato de la raiz: " << arbol.obtenerDatoRaiz().get_tipo() << endl;
      } catch (const std::runtime_error& e) {
    std::cout << "Error: " << e.what() << std::endl;
      }

      arbol.preOrden(arbol.obtenerRaiz());
      cout << endl;*/

      //cout << arbol.obtenerRaiz()->getHijo(4);
    
        return true;
      }
  else if (comando[0]=="en_cuadrante" && comando.size()== 5 ){
    /*if(!arbol.esVacio()){
          cout << "Holi" << endl;
        }else{
          cout << "Vacio" << endl;
        }*/
        robot.en_cuadrante(stoi(comando[1]), stoi(comando[2]), stoi(comando[3]), stoi(comando[4]), arbol);
        return true;
      }
  else if (comando[0]=="crear_mapa" && comando.size()== 2 ){
        robot.crear_mapa(stof(comando[1]), g);
    
        /*std::vector< Elemento > vertices = g.ObtenerVertices();
    std::cout << "Vértices: ";
    for (auto& vertice : vertices) {
        std::cout << vertice.get_tipo() << " ";
    }
    std::cout << std::endl;

    unsigned long numVertices = g.NumeroVertices();

        std::cout << "Costos de aristas:" << std::endl;
    for (unsigned long i = 0; i < numVertices; ++i) {
        for (unsigned long j = 0; j < numVertices; ++j) {
          if(i != j){
            double costo = g.ObtenerCosto(i, j);
          if(costo < 9999){
            std::cout << "Arista (" << vertices[i] << ", " << vertices[j] << "): " << costo << std::endl;
          }else{
            std::cout << "Arista (" << vertices[i] << ", " << vertices[j] << "): " << 0 << std::endl;
          }
          }
        }
    }*/

    return true;
    
      } else if (comando[0]=="ruta_mas_larga" && comando.size()== 1 ){
        robot.ruta_mas_larga(g);
        return true;
      }
    
  else if(comando[0] == "ayuda" && comando.size()==1){
      cout << "Los comandos disponibles (primera palabra), con sus respectivos parametros son:\n- cargar_comandos nombre_archivo\n- cargar_elementos nombre_archivo\n- agregar_movimiento tipo_mov magnitud unidad_med\n- agregar_analisis tipo_analisis objeto comentario\n- agregar_elemento tipo_comp tamaño unidad_med coordX coordY\n- guardar tipo_archivo nombre_archivo\n- simular_comandos coordX coordY\n- salir\n- ubicar_elementos\n- en_cuadrante coordX1 coordX2 coordY1 coordY2\n- crear_mapa coeficiente conectividad\n- ruta_mas_larga\n" << endl;
      return true;
      
  }else{
      return false;
    }   
}

int main() {
    Robot robot("Curiosity");
    TArbol arbol;
    TGraph g;
    vector<string> comando;
    string comandoaux;
    int num_aux = 1, num_elem = 0;
    bool valido = false;
    //cin.ignore();
    do{
      cout << "$";
      getline(cin, comandoaux);
      comandoaux = lowerCase(comandoaux);
      comando = separar_palabras(comandoaux);
      valido = validarComando(comando, robot, num_aux, num_elem, arbol, g);
      /*if(valido){
        cout << "Comando valido" << endl;
      }else{
        cout << "Comando invalido" << endl;
      }*/
      if(!valido){
        cout << "Comando invalido" << endl;
      }
   }while(comando[0]!="salir");
    return 0;
  }