/*
################
#### TIMERS ####
################
Autor: Ing. Angel Molina

Descripción: Este es un archivo main.c de ejemplo para demostrar cómo se utilizan las funciones de la biblioteca.

Objetivo: El objetivo de la librería es aprender a iniciar un timer simple. En este ejemplo, el timer ejecuta una función Callback cada 1 segundo.

**  Al momento de descargar la librería, será necesario copiar los archivos .h y .c en la carpeta /main/components
*** Al momento de descargar la librería, será necesario incluir el archivo .c en el archivo CMake.txt ***
*/

#include <stdio.h> // Librería estandar de C para inputs/outputs
#include "components/myModules/simple_timer.h" // Aquí se debe agregar la librería que se va a utilizar

TimerHandle_t miTimer;

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("### TIMERS ###\n");
    set_timer(&miTimer, 1000, 1, vTimerCallback__prototipo__);
}