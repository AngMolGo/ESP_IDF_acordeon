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

#ifndef SIMPLE_TIMER_H_INCLUDED
#define SIMPLE_TIMER_H_INCLUDED

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_log.h"

esp_err_t set_timer(TimerHandle_t *xTimer, int interval_ms, int timerID, TimerCallbackFunction_t *function_callback);
void vTimerCallback__prototipo__(TimerHandle_t pxTimer); // Ejemplo de una función de callbak que manda a llamar el timer

#endif // SIMPLE_TIMER_H_INCLUDED