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

#include <stdio.h> // Librería estandar de C para inputs/outputs en la terminal
#include "components/myModules/simple_adc.h" // Aquí se debe agregar la librería que se va a utilizar

#include "freertos/FreeRTOS.h"  // ESTAS LIBRERÍAS SON PROVICIONALES,
#include "freertos/task.h"      // TODAVÍA NO VEMOS NADA DE FREERTOS.

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("\n### ADC - Analog Digital Converter ###\n");

    // Inicialización del adc1
    adc_oneshot_unit_handle_t handle_adc1;
    set_adc_init(&handle_adc1);
    // Inicialización del channel0 -> (GPIO 36 - SP - ADC1_0)
    set_adc_channel(&handle_adc1, ADC_CHANNEL_0);

    int data; // Variable que almacena el dato "crudo" del adc

    while(1){
        adc_oneshot_read(handle_adc1, ADC_CHANNEL_0, &data); // Lectura de dato "crudo" yque se asigna a la variable "data"
        printf("\nValor leído: %d", data);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}