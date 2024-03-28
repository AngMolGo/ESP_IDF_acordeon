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

#ifndef SIMPLE_PWM_H_INCLUDED
#define SIMPLE_PWM_H_INCLUDED

#include "driver/ledc.h" // Agregamos la librería "led control"

/**
     * @brief my function update TIMER (inside signal) parameters
     *
     * @note El canal es una señal de salida, determina las características de la salida del pwm del gpio (duty, timers que ayudan al pwm específico)
     *       El timer es una señal interna, determina las características de la onda pwm cruda (frecuencia, resolución, timer que ayuda formación del tren de impulsos)
     *
     * @param resolution !< LEDC channel duty resolution. Ex: LEDC_TIMER_10_BIT, etc.
     * @param hz !< LEDC timer frequency (Hz) Ej: 20000 hz
     *
     * @return
     *     - ESP_OK Success
     */
esp_err_t set_pwm_timer(ledc_timer_bit_t resolution, uint32_t hz); // Se configura una sola vez

/**
     * @brief my function update CHANNEL (outside signal) parameters
     *
     * @note El canal es una señal de salida, determina las características de la salida del pwm del gpio (duty, timers que ayudan al pwm específico)
     *       El timer es una señal interna, determina las características de la onda pwm cruda (frecuencia, resolución, timer que ayuda formación del tren de impulsos)
     *
     * @param gpio_num Selecciona la salida GPIO del canal, pueden ser dos gpios por un mismo canal pero se ejecuta la función por separado por cada gpio.
     * @param channel Selecciona el canal de salida. Ex: LEDC_CHANNEL_0, LEDC_CHANNEL_1, etc.
     *
     * @return
     *     - ESP_OK Success
     */
esp_err_t set_pwm_channel(int gpio_num, ledc_channel_t channel); // Se configura una por canal

/**
     * @brief my function update CHANNEL (outside signal) parameters
     *
     * @note El canal es una señal de salida, determina las características de la salida del pwm del gpio (duty, timers que ayudan al pwm específico)
     *       El timer es una señal interna, determina las características de la onda pwm cruda (frecuencia, resolución, timer que ayuda formación del tren de impulsos)
     *
     * @param channel Selecciona el canal de salida. Ex: LEDC_CHANNEL_0, LEDC_CHANNEL_1, etc.
     * @param duty [0 - (LEDC_TIMER_RESOLUTION_BIT^2-1)]
     *
     * @return
     *     - ESP_OK Success
     */
esp_err_t set_pwm_duty(ledc_channel_t channel, uint32_t duty); // Se puede utilizar durante todo el código

#endif // SIMPLE_PWM_H_INCLUDED