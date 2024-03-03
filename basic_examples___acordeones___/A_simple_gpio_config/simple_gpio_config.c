/*
Para implementar librería en C se recomienda usar dos archivos: miModulo.h y miModulo.c

-> miModulo.h: Contiene las *declaraciones* de todas las variables de una biblioteca.
               Le informa al compilador sobre la existencia de una entidad en el programa.
               Puede incluir variables, funciones o clases.

-> miModulo.c: Contiene las *definiciones* de las variables descritas en el archivo miModulo.h.
               Se proporcionan los detalles de la implementación de cada variable/función.
               En el caso de funciones, se describe el cuerpo de la función.

*** Por ultimo pero no menos importante, es importante que al momento de agregar nuevas librerías/archivos
    se declaren en el archivo CMake.txt de la carpeta /main ***
*/

#include "simple_gpio_config.h" // Se incluye el archivo .h de nuestra biblioteca

esp_err_t init_pin(gpio_num_t pin, gpio_mode_t value){
    gpio_reset_pin(pin); // Se reinicia la configuración del pin
    gpio_set_direction(pin, value); // Se configura la dirección input/output del pin
    return ESP_OK;
}


esp_err_t digitalWrite(gpio_num_t pin, bool value){
    gpio_set_level(pin, value);
    return ESP_OK;
}