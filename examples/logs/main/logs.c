/* Uso de logs */

#include <stdio.h>   // Librería estandar de C para inputs/outputs
#include "esp_log.h" // Librería para "arrojar" logs en consola

static const char *TAG = "ESP32"; // El 'TAG' es una etiqueta que se utiliza para identificar la fuente del mensaje de registro.

void app_main(void) // Función principal de un programa de ESP32, el firmware busca esta función para empezar operaciones.
{
    printf("\n# # # USO DE LOGS # # #\n\n");
    
    printf("El 'TAG' es una etiqueta que se utiliza para identificar la fuente del mensaje de registro.\n\n");
    ESP_LOGI(TAG, "*** Hola mundo (INFORMATIVO) ***");
    printf("Esta funcion se utiliza para imprimir mensajes de informacion.\nEs útil para imprimir mensajes que proporcionan información sobre el estado del programa o los datos procesados.\n\n");
    ESP_LOGW(TAG, "*** Hola mundo (WARNING) ***");
    printf("Se utiliza para imprimir mensajes de advertencia.\nEstos mensajes indican condiciones que podrían ser problemáticas o inesperadas, pero que no necesariamente causan un fallo en el programa.\n\n");
    ESP_LOGE(TAG, "*** Hola mundo (ERROR) ***");
    printf("Se utiliza para imprimir mensajes de error.\nEstos mensajes indican condiciones de error que requieren la atención del desarrollador y pueden indicar problemas graves que afectan el funcionamiento del programa.\n\n");
    ESP_LOGD(TAG, "*** Hola mundo (DEBUGGING) ***");
    printf("Se utiliza para imprimir mensajes de depuración.\nEstos mensajes se utilizan durante el desarrollo para proporcionar información detallada sobre el funcionamiento del programa que puede ser útil para depurar problemas.\n\n");
    ESP_LOGV(TAG, "*** Hola mundo (VERBOSIDAD) ***");
    printf("NOTA: Se utiliza para imprimir mensajes de verbosidad.\nEstos mensajes son los más detallados y se utilizan para proporcionar una salida muy detallada sobre el funcionamiento interno del programa. Son útiles para la depuración intensiva o para imprimir información detallada en situaciones específicas.\n\n");
    printf("\n*** Si no se puede visualizar los LOGS de debug y verbosity es porque se tiene que configurar los niveles de LOGGING permitido\n\n");
}