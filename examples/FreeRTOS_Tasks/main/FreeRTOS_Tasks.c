#include <stdio.h> // Librería estándar de C para inputs/outputs en la terminal

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Declaración de las funciones
esp_err_t init_pin(gpio_num_t pin, gpio_mode_t value);
esp_err_t pinON(gpio_num_t pin);
esp_err_t pinOFF(gpio_num_t pin);

void mi_vTask1(void *pvParameters);
void mi_vTask2(void *pvParameters);

esp_err_t create_tasks(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior);
esp_err_t create_tasks_to_core(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior, BaseType_t core_assigned);

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("\n### FreeRTOS - Tasks ###\n");

    printf("\n-> Number of cores: %i\n", portNUM_PROCESSORS);

    // Inicializa los pines GPIO como salidas
    init_pin(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    init_pin(GPIO_NUM_18, GPIO_MODE_OUTPUT);

    // Crea las tareas, asignándolas a los núcleos correspondientes
    create_tasks(mi_vTask1, "Tarea 1", 1024 * 2, 1);
    create_tasks_to_core(mi_vTask2, "Tarea 2", 1024 * 2, 2, 1);

    // Bucle principal donde se imprime "Hola Mundo"
    while (1)
    {
        printf("\nHola mundo");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1 segundo
    }
}

void mi_vTask1(void *pvParameters)
{
    while (1)
    {
        printf("\nLed 18");
        pinON(GPIO_NUM_18);             // Enciende el LED en GPIO18
        vTaskDelay(pdMS_TO_TICKS(400)); // Espera 400 ms
        pinOFF(GPIO_NUM_18);            // Apaga el LED en GPIO18
        vTaskDelay(pdMS_TO_TICKS(400)); // Espera 400 ms
    }
}

void mi_vTask2(void *pvParameters)
{
    while (1)
    {
        printf("\nLed 5");
        pinON(GPIO_NUM_5);              // Enciende el LED en GPIO5
        vTaskDelay(pdMS_TO_TICKS(550)); // Espera 550 ms
        pinOFF(GPIO_NUM_5);             // Apaga el LED en GPIO5
        vTaskDelay(pdMS_TO_TICKS(550)); // Espera 550 ms
    }
}

esp_err_t create_tasks(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior)
{
    TaskHandle_t xHandle = NULL;

    // Crea una tarea sin asignarla a un núcleo específico
    if (xTaskCreate(
        func_task,          // Función de la tarea
        funcName,           // Nombre de la tarea
        tam,                // Tamaño de la pila
        NULL,               // Parámetros de la tarea
        prior,              // Prioridad de la tarea
        &xHandle            // Handle de la tarea
    ) != pdPASS) {
        printf("Error al crear la tarea %s\n", funcName);
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t create_tasks_to_core(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior, BaseType_t core_assigned)
{
    TaskHandle_t xHandle = NULL;

    // Crea una tarea asignada a un núcleo específico
    if (xTaskCreatePinnedToCore(
        func_task,          // Función de la tarea
        funcName,           // Nombre de la tarea
        tam,                // Tamaño de la pila
        NULL,               // Parámetros de la tarea
        prior,              // Prioridad de la tarea
        &xHandle,           // Handle de la tarea
        core_assigned       // Núcleo asignado
    ) != pdPASS) {
        printf("Error al crear la tarea %s en el núcleo %d\n", funcName, core_assigned);
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t init_pin(gpio_num_t pin, gpio_mode_t value)
{
    // Reinicia la configuración del pin y luego establece la dirección
    gpio_reset_pin(pin);            // Reinicia la configuración del pin
    gpio_set_direction(pin, value); // Configura el pin como entrada o salida
    return ESP_OK;
}

esp_err_t pinOFF(gpio_num_t pin)
{
    // Apaga el pin (lo pone en nivel bajo)
    gpio_set_level(pin, 0);
    return ESP_OK;
}

esp_err_t pinON(gpio_num_t pin)
{
    // Enciende el pin (lo pone en nivel alto)
    gpio_set_level(pin, 1);
    return ESP_OK;
}
