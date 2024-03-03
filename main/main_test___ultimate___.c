/*
###############################
#### Plantilla de proyecto ####
###############################
Autor: Ing. Angel Molina

Descripción: El objetivo de esta plantilla es ayudar a aprender a programar una esp32 desde
             el SDK recomendado por Espressif. La intensión es desarrollar varios ejemplos
             sencillos para la fácil comprensión de un estudiante que venga programando en
             el Arduino IDE y no se le dificulte la transición.

             En el arbol de archivos se encontrarán diferentes recursos para aprender a
             utilizar los diferentes periféricos que ofrece la ESP32.

             *** Será necesario incluir los archivos .c de las librería que se vayan a utilizar en el archivo CMake.txt. ***
*/

#include <stdio.h> // Librería estandar de C para inputs/outputs

// Éste es un include incluye una función de testeo para comprobar que se está importando mi librería de prueba. 
// En esa dirección se incluirán las librerías personales que se crearán después.
#include "components/myModules/firstTest.h"

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    saludar(); // Implementación de la función importada desde "firstTest.h"
} 