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

#include "simple_timer.h" // Se incluye el archivo .h de nuestra biblioteca

void vTimerCallback__prototipo__(TimerHandle_t pxTimer){
    printf("Hola mundo desde el timer\n");
}

esp_err_t set_timer(TimerHandle_t *xTimer, int interval_ms, int timerID, TimerCallbackFunction_t *function_callback)
{
    char *tag = "Timer creator";
    ESP_LOGI(tag, "Timer init configuration");
    *xTimer = xTimerCreate("Timer",                      // Text name for the task.  Helps debugging only.  Not used by FreeRTOS.
                          (pdMS_TO_TICKS(interval_ms)), // The period of the timer in ticks.
                          pdTRUE,                       // This is an auto-reload timer.
                          (void *)timerID,              // A variable incremented by the software timer's callback function
                          function_callback);           // The function to execute when the timer expires.

    if (*xTimer == NULL)
        ESP_LOGE(tag, "The timer was not created");
    else
    {
        if (xTimerStart(*xTimer, 0) != pdPASS)

            ESP_LOGE(tag, "The timer could not be set into the Active state");
    }
    return ESP_OK;
}