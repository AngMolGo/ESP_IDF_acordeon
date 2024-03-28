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

#ifndef SIMPLE_ADC_H_INCLUDED
#define SIMPLE_ADC_H_INCLUDED

#include "esp_adc/adc_oneshot.h"

/**
 * @brief Configure ADC1 capture width, meanwhile enable output invert for ADC1.
 *        The configuration is for all channels of ADC1
 * @param adc_handle Bit capture width for ADC1
 *
 * @return
 *     - ESP_OK success
 */
esp_err_t set_adc_init(adc_oneshot_unit_handle_t *adc_handle);

/**
 * @brief Configure ADC1 capture width, meanwhile enable output invert for ADC1.
 *        The configuration is for all channels of ADC1
 * @param adc_handle Bit capture width for ADC1
 * 
 * @param channel Bla bla bla
 *
 * @return
 *     - ESP_OK success
 */
esp_err_t set_adc_channel(adc_oneshot_unit_handle_t *adc_handle, adc_channel_t channel);

#endif // SIMPLE_ADC_H_INCLUDED