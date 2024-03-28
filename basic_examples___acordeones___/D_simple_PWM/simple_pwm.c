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

#include "simple_pwm.h" // Se incluye el archivo .h de nuestra biblioteca

esp_err_t set_pwm_timer(ledc_timer_bit_t resolution, uint32_t hz)
{

    ledc_timer_config_t timerConfig = {0}; // Para el PWM en general
    timerConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    timerConfig.duty_resolution = resolution;
    timerConfig.timer_num = LEDC_TIMER_0; // Aguas con la aplicación de timers, ya utiliza el timer 0 con esta aplicación.
    timerConfig.freq_hz = hz;             // 20kHz

    ledc_timer_config(&timerConfig);

    return ESP_OK;
}

esp_err_t set_pwm_channel(int gpio_num, ledc_channel_t channel)
{

    ledc_channel_config_t channelConfig = {0};
    channelConfig.gpio_num = gpio_num;
    channelConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    channelConfig.channel = channel;
    channelConfig.intr_type = LEDC_INTR_DISABLE;
    channelConfig.timer_sel = LEDC_TIMER_0;
    channelConfig.duty = 0;

    ledc_channel_config(&channelConfig);

    return ESP_OK;
}

esp_err_t set_pwm_duty(ledc_channel_t channel, uint32_t duty)
{

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, channel, duty); // Actualiza el PARÁMETRO de duty del PWM

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, channel); // Actualiza la SALIDA FISICA del periférico

    return ESP_OK;
}