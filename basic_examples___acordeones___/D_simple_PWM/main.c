/*
###################################
#### [INSERTAR DE QUÉ TRATA ESTE EJEMPLO] ####
###################################
Autor: Ing. Angel Molina

Descripción: Este es un archivo main.c de ejemplo para demostrar cómo se utilizan las funciones de la biblioteca.

Objetivo: [OBJETIVO DE LA BIBLIOTECA]

**  Al momento de descargar la librería, será necesario copiar los archivos .h y .c en la carpeta /main/components
*** Al momento de descargar la librería, será necesario incluir el archivo .c en el archivo CMake.txt ***
*/

#include "freertos/FreeRTOS.h"  // ESTAS LIBRERÍAS SON PROVICIONALES,
#include "freertos/task.h"      // TODAVÍA NO VEMOS NADA DE FREERTOS.

#include <stdio.h> // Librería estandar de C para inputs/outputs en la terminal
#include "components/myModules/simple_pwm.h" // Aquí se debe agregar la librería que se va a utilizar

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("\n### Simple PWM ###\n");

    // Configuración
    set_pwm_timer(LEDC_TIMER_10_BIT, 20000);
    set_pwm_channel(18, LEDC_CHANNEL_0);
    set_pwm_channel(5, LEDC_CHANNEL_1);

    // Aplicación: Carga y descarga
    for(int i = 0; i <1020; i++){
        set_pwm_duty(LEDC_CHANNEL_0, i);
        set_pwm_duty(LEDC_CHANNEL_1, i);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    for(int i = 1020; i >= 0; i--){
        set_pwm_duty(LEDC_CHANNEL_0, i);
        set_pwm_duty(LEDC_CHANNEL_1, i);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}