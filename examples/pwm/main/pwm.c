#include <stdio.h>
#include "driver/ledc.h"       // Agregamos la librería "led control"
#include "freertos/FreeRTOS.h" // ESTAS LIBRERÍAS SON PROVICIONALES,
#include "freertos/task.h"     // TODAVÍA NO VEMOS NADA DE FREERTOS.

#include "math.h"

esp_err_t set_pwm_timer(ledc_timer_bit_t resolution, uint32_t hz);
esp_err_t set_pwm_channel(int gpio_num, ledc_channel_t channel);
esp_err_t set_pwm_duty(ledc_channel_t channel, uint32_t duty);

void app_main(void)
{
    printf("\n# # # Simple PWM # # #\n");

    // Configuración
    set_pwm_timer(LEDC_TIMER_10_BIT, 20000);
    set_pwm_channel(22, LEDC_CHANNEL_0);
    set_pwm_channel(5, LEDC_CHANNEL_1);

    // Aplicación: Carga y descarga
    while (1)
    {
        for (int i = 0; i <= 100; i++)
        {
            double pwm = 1020 * (exp(i / 100.0) - 1) / (exp(1) - 1);
            //printf("i: %d, pwm: %f\n", i, pwm);
            set_pwm_duty(LEDC_CHANNEL_0, (int)pwm);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        for (int i = 100; i >= 0; i--)
        {
            double pwm = 1020 * (exp(i / 100.0) - 1) / (exp(1) - 1);
            set_pwm_duty(LEDC_CHANNEL_0, (int)pwm);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

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