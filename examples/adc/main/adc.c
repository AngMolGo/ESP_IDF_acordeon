#include <stdio.h>
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    printf("\n### ADC2 - Analog Digital Converter ###\n");

    // Inicializar ADC2
    adc_oneshot_unit_handle_t handle_adc2;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };

    esp_err_t err = adc_oneshot_new_unit(&init_config, &handle_adc2);
    if (err != ESP_OK) {
        printf("Error en la inicialización del ADC: %d\n", err);
        return;
    }

    // Configurar canal 8 del ADC2
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT, // Usa el ancho por defecto (normalmente 12 bits)
        .atten = ADC_ATTEN_DB_11 // Rango hasta 3.3V
    };

    err = adc_oneshot_config_channel(handle_adc2, ADC_CHANNEL_8, &config);
    if (err != ESP_OK) {
        printf("Error en la configuración del canal: %d\n", err);
        return;
    }

    int data;
    while (1) {
        err = adc_oneshot_read(handle_adc2, ADC_CHANNEL_8, &data);
        if (err == ESP_OK) {
            printf("Valor leído: %d\n", data);
        } else {
            printf("Error al leer ADC2: %d\n", err);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}



esp_err_t set_adc_init(adc_oneshot_unit_handle_t *adc_handle)
{
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE};

    esp_err_t err = adc_oneshot_new_unit(&init_config1, adc_handle);
    if (err != ESP_OK) {
        printf("Error en adc_oneshot_new_unit: %d\n", err);
        return err;
    }

    return ESP_OK;
}

esp_err_t set_adc_channel(adc_oneshot_unit_handle_t *adc_handle, adc_channel_t channel)
{
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_10,
        .atten = ADC_ATTEN_DB_12};

    esp_err_t err = adc_oneshot_config_channel(*adc_handle, channel, &config);
    if (err != ESP_OK) {
        printf("Error en adc_oneshot_config_channel: %d\n", err);
        return err;
    }

    return ESP_OK;
}
