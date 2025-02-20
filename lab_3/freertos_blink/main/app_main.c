#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_control.h"

#define TAG "MAIN"

// FreeRTOS task that replaces app_main()
void app_main_task(void *arg)
{
    ESP_LOGI(TAG, "Initializing LEDs...");
    init_leds();

    ESP_LOGI(TAG, "Starting LED Blink Tasks...");
    for (int i = 0; i < 3; i++)
    {
        xTaskCreate(blink_led_task, leds[i].color, 2048, (void *)&leds[i], 1, NULL);
    }

    xTaskCreate(log_status_task, "Log Task", 2048, NULL, 1, NULL);

    ESP_LOGI(TAG, "App main task finished setup, deleting itself...");

    // Self-delete this task to free resources
    vTaskDelete(NULL);
}

// Standard app_main() only creates app_main_task
void app_main(void)
{
    xTaskCreate(app_main_task, "App Main Task", 4096, NULL, 1, NULL);
}
