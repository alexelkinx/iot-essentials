#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gpio_lights.h"
#include "traffic_light_logic.h"
#include "esp_log.h"

static const char *TAG = "APP_MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing lights...");
    init_lights();

    ESP_LOGI(TAG, "Setting initial time to 05:59...");
    set_time(5, 59, 0); // Set initial time to 05:59

    while (1)
    {
        traffic_color_t color = next_second();
        set_lights(color);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
    }
}