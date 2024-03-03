/*
Para implementar librería en C se recomienda usar dos archivos: miModulo.h y miModulo.c

-> miModulo.h: Contiene las *declaraciones* de todas las variables de una biblioteca.
               Le informa al compilador sobre la existencia de una entidad en el programa.
               Puede incluir variables, funciones o clases.
               Aquí también se incluyen las inclusiones de las librerías utilizadas.

-> miModulo.c: Contiene las *definiciones* de las variables descritas en el archivo miModulo.h.
               Se proporcionan los detalles de la implementación de cada variable/función.
               En el caso de funciones, se describe el cuerpo de la función.

*** Por ultimo pero no menos importante, es importante que al momento de agregar nuevas librerías/archivos
    se declaren en el archivo CMake.txt de la carpeta /main ***
*/

#ifndef SIMPLE_GPIO_CONFIG_H_INCLUDED
#define SIMPLE_GPIO_CONFIG_H_INCLUDED

#include "esp_err.h"
#include "driver/gpio.h"
#include <stdbool.h>

esp_err_t init_pin(gpio_num_t pin, gpio_mode_t value);
esp_err_t digitalWrite(gpio_num_t pin, bool value);

#endif // SIMPLE_GPIO_CONFIG_H_INCLUDED