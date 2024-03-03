/*
###################################
#### SIMPLE GPIO CONFIGURATION ####
###################################
Autor: Ing. Angel Molina

Descripción: Este es un archivo main.c de ejemplo para demostrar cómo se utilizan las funciones de la biblioteca.

Objetivo: Configurar los pines GPIO de la ESP32.

**  Al momento de descargar la librería, será necesario copiar los archivos .h y .c en la carpeta /main/components
*** Al momento de descargar la librería, será necesario incluir el archivo .c en el archivo CMake.txt ***
*/

#include <stdio.h> // Librería estandar de C para inputs/outputs
#include "components/myModules/simple_gpio_config.h"

#define pin 18 // Se define el número de pin que queremos configurar

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("### Configuración básica de un pin ###");

    init_pin(pin, GPIO_MODE_OUTPUT); // Configura el pin como salida
    pinON(pin);         // Cambia el valor de salida del pin
}