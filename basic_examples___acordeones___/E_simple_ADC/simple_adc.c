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

#include "simple_adc.h" // Se incluye el archivo .h de nuestra biblioteca

esp_err_t set_adc_init(adc_oneshot_unit_handle_t *adc_handle)
{

    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE};

    adc_oneshot_new_unit(&init_config1, adc_handle);

    return ESP_OK;
}

esp_err_t set_adc_channel(adc_oneshot_unit_handle_t *adc_handle, adc_channel_t channel)
{

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_10,
        .atten = ADC_ATTEN_DB_12};

    adc_oneshot_config_channel(*adc_handle, channel, &config);

    return ESP_OK;
}

