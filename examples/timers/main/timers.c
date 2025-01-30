#include <stdio.h>             // Librería estándar de C para entrada/salida
#include "driver/gpio.h"       // Control de pines GPIO (no lo usamos aquí, pero se puede eliminar si no es necesario)
#include "freertos/FreeRTOS.h" // Biblioteca principal de FreeRTOS
#include "freertos/timers.h"   // Biblioteca para el manejo de temporizadores en FreeRTOS
#include "esp_log.h"           // Librería para logs en ESP-IDF

#define TIMER_INTERVAL_MS 1000 // Intervalo del temporizador en milisegundos (1 segundo)

TimerHandle_t miTimer; // Declaración del temporizador

/**
 * @brief Función para crear e iniciar un temporizador
 *
 * @param xTimer Puntero a la variable del temporizador
 * @param interval_ms Intervalo en milisegundos
 * @param timerID Identificador del temporizador
 * @param function_callback Función de callback que se ejecutará cuando el temporizador expire
 * @return esp_err_t ESP_OK si se creó e inició correctamente, ESP_FAIL en caso de error
 */
esp_err_t set_timer(TimerHandle_t *xTimer, int interval_ms, int timerID, TimerCallbackFunction_t function_callback);

/**
 * @brief Función de callback que se ejecutará cada vez que expire el temporizador
 *
 * @param pxTimer Manejador del temporizador que activó el callback
 */
void vTimerCallback(TimerHandle_t pxTimer);

void app_main(void) // Función principal que se ejecuta al iniciar el programa en ESP32
{
    printf("# # # TIMERS # # #\n"); // Mensaje inicial en la consola

    // Crear e iniciar el temporizador con un intervalo de TIMER_INTERVAL_MS milisegundos
    set_timer(&miTimer, TIMER_INTERVAL_MS, 0, vTimerCallback);
}

/**
 * @brief Función de callback que se ejecuta cuando el temporizador expira.
 *
 * @param pxTimer Manejador del temporizador que activó el callback
 */
void vTimerCallback(TimerHandle_t pxTimer)
{
    printf("Hola mundo desde el timer\n"); // Mensaje que indica que el temporizador está funcionando
}

/**
 * @brief Función para configurar e iniciar un temporizador en FreeRTOS
 *
 * @param xTimer Puntero a la variable del temporizador
 * @param interval_ms Intervalo en milisegundos
 * @param timerID Identificador del temporizador
 * @param function_callback Función de callback que se ejecutará cuando el temporizador expire
 * @return esp_err_t ESP_OK si se creó e inició correctamente, ESP_FAIL en caso de error
 */
esp_err_t set_timer(TimerHandle_t *xTimer, int interval_ms, int timerID, TimerCallbackFunction_t function_callback)
{
    char *tag = "Timer Creator";                        // Etiqueta para logs
    ESP_LOGI(tag, "Iniciando configuración del Timer"); // Mensaje de inicio en la consola

    // Crear el temporizador en modo "Auto-reload" (se reinicia automáticamente después de cada expiración)
    *xTimer = xTimerCreate(
        "Timer",                    // Nombre del temporizador (solo para depuración)
        pdMS_TO_TICKS(interval_ms), // Período del temporizador en ticks (conversión de milisegundos a ticks)
        pdTRUE,                     // Temporizador en modo auto-reload (se reinicia automáticamente)
        (void *)(intptr_t)timerID,  // ID del temporizador (convertido a puntero para evitar warnings)
        function_callback           // Función de callback a ejecutar cuando el temporizador expire
    );

    // Verificar si el temporizador se creó correctamente
    if (*xTimer == NULL)
    {
        ESP_LOGE(tag, "El temporizador no pudo ser creado"); // Error si falló la creación
        return ESP_FAIL;
    }
    else
    {
        // Iniciar el temporizador
        if (xTimerStart(*xTimer, 0) != pdPASS)
        {
            ESP_LOGE(tag, "El temporizador no pudo ser iniciado"); // Error si falló el inicio
            return ESP_FAIL;
        }
    }

    return ESP_OK; // Retorna éxito si todo salió bien
}
