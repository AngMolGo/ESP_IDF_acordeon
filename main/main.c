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
*/

#include <stdio.h> // Librería estandar de C para inputs/outputs

#include "components/myModules/firstTest.h"

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    saludar();
}