# RobotEnMarte
Proyecto en c++ donde se debe ayudar a un hipotético robot enviado a Marte a ejecutar comandos que describen los movimientos que debe realizar y los elementos ubicados a sus alrededores.

Para correr el programa, se pueden ejecutar las siguientes línes de código en la consola: "g++ main.cpp ArbolQuad.hxx Comando_analisis.cxx Comando_movimiento.cxx Elemento.cxx Grafo.hxx NodoQuadtree.hxx Robot.cxx -
o mi_programa" y "./mi_programa".

Para conocer los comandos disponibles se debe escribir "ayuda" después del signo '$' que aparecerá a la hora de ingresar cualquier comando, esto mostrará el nombre de todos los comandos junto a los paramétros necesarios para cada uno de ellos; algunos no requieren paramétros y otros requieren la ejecución previa de otros comandos para su correcto funcionamiento.

Para conocer la descripción de algún comando específico, se debe escribir la palabra "ayuda" seguido del nombre del comando del cual se requiere información, nuevamente todo después del signo '$'.

Finalmente, para "cargar_comandos" y "cargar_elementos", se requiere la existencia de archivos de texto de los cuales cargar la información. Se adjuntan los archivos "comandos_desplazamiento.txt" y "elementos.txt" que se pueden usar como ejemplo y base para el correcto funcionamiento del programa.

