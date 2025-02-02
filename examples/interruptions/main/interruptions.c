#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void idr_funct(void *args);
static bool flag = false;
static int led_turn = 0;

esp_err_t create_tasks(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior);
esp_err_t init_isr();
void mi_vTask1(void *pvParameters);

void app_main(void)
{
    create_tasks(mi_vTask1, "Tarea 1", 1024 * 2, 1);
    init_isr();

    gpio_reset_pin(GPIO_NUM_18);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_18, 0);
    
    gpio_reset_pin(GPIO_NUM_5);
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_5, 0);
    
    gpio_reset_pin(GPIO_NUM_17);
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_17, 0);

    gpio_reset_pin(GPIO_NUM_16);
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_16, 0);

    gpio_reset_pin(GPIO_NUM_23);
    gpio_set_direction(GPIO_NUM_23, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_23, 0);

    while (true)
    {
        gpio_set_level(GPIO_NUM_23, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
        gpio_set_level(GPIO_NUM_23, 1);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

static void idr_funct(void *args){
    flag = true;
}

esp_err_t init_isr()
{
    gpio_config_t isr_pin_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_4),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };

    gpio_config(&isr_pin_config);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_4, idr_funct, NULL);

    return ESP_OK;
}

esp_err_t create_tasks(void (*func_task)(void *), const char *const funcName, const uint32_t tam, UBaseType_t prior)
{
    TaskHandle_t xHandle = NULL;

    if (xTaskCreate(
            func_task,
            funcName,
            tam,
            NULL,
            prior,
            &xHandle) != pdPASS)
    {
        printf("Error al crear la tarea %s\n", funcName);
        return ESP_FAIL;
    }

    return ESP_OK;
}

void mi_vTask1(void *pvParameters)
{
    while (1)
    {
        if (flag)
        {
            flag = false;
            led_turn++;
            if (led_turn == 4) led_turn = 0;
        }

        gpio_set_level(GPIO_NUM_16, (led_turn == 0));
        gpio_set_level(GPIO_NUM_17, (led_turn == 1));
        gpio_set_level(GPIO_NUM_5, (led_turn == 2));
        gpio_set_level(GPIO_NUM_18, (led_turn == 3));

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
