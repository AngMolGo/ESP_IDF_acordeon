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

#include "simple_freertos_task_creation.h" // Se incluye el archivo .h de nuestra biblioteca

esp_err_t create_tasks(void (*func_task)(), const char *const funcName, const uint32_t tam, UBaseType_t prior){
    
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;
    
    xTaskCreate(
        func_task,
        funcName,
        tam,
        &ucParameterToPass,
        prior,
        &xHandle
    );

    return ESP_OK;
}

esp_err_t create_tasks_to_core(void (*func_task)(), const char *const funcName, const uint32_t tam, UBaseType_t prior, const BaseType_t core_assigned){
    
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;
    
    xTaskCreatePinnedToCore(
        func_task,
        funcName,
        tam,
        &ucParameterToPass,
        prior,
        &xHandle,
        core_assigned
    );

    return ESP_OK;
}