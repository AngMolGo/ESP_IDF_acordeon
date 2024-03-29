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
#include "components/myModules/simple_freertos_task_creation.h" // Aquí se debe agregar la librería que se va a utilizar
#include "components/myModules/simple_gpio_config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

esp_err_t mi_vTask1(void * pvParameters);
esp_err_t mi_vTask2(void * pvParameters);

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("\n### FreeRTOS - Tasks ###\n");

    printf("\n-> Number of cores: %i\n", portNUM_PROCESSORS);

    init_pin(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    init_pin(GPIO_NUM_18, GPIO_MODE_OUTPUT);

    create_tasks(mi_vTask1, "Tarea 1", 1024*2, 1);
    create_tasks_to_core(mi_vTask2, "Tarea 2", 1024*2, 2, 1);

    while(1){
        printf("\nHola mundo");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}

esp_err_t mi_vTask1(void * pvParameters){
    while(1){
        printf("\nLed 18");
        pinON(GPIO_NUM_18);
        vTaskDelay(pdMS_TO_TICKS(400));
        pinOFF(GPIO_NUM_18);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

esp_err_t mi_vTask2(void * pvParameters){
    while(1){
        printf("\nLed 5");
        pinON(GPIO_NUM_5);
        vTaskDelay(pdMS_TO_TICKS(550));
        pinOFF(GPIO_NUM_5);
        vTaskDelay(pdMS_TO_TICKS(550));
    }
}