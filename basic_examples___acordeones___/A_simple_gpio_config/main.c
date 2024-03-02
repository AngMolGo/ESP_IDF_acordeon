/* Blink simple */

#include <stdio.h> // Librería estandar de C para inputs/outputs
#include "driver/gpio.h" // Funciones para interactuar con pines: lectura, escritura, config. de dirección, interrupciones, etc.
#include "freertos/FreeRTOS.h" // Biliboteca de FreeRTOS. Sirve para gestionar tareas, planificación de tiempo y recursos del sistema. Funciones y definiciones neceserias para FreeRTOS en ESP32.
#include "freertos/task.h" // Proporciona funciones y macros para creación, gestión y control de las tareas (threads) en FreeRTOS. (Crear, suspender, reanudar, eliminar, cambiar prioridad, etc.)

#include "basic_examples___acordeones___\A_simple_gpio_config\simple_gpio_config.h"

#define led1 2 // Número de pin

uint8_t led_level = 0; // Estado del pin (Alto/Bajo)

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("Hola mundo"); // Simple Hola mundo
}