#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_6 // Specify the correct GPIO (6)
#define BLINK_DELAY 100     // Delay in milliseconds (1 second)
#define TAG "BLINK_APP"

void app_main()
{
    esp_log_level_set(TAG, ESP_LOG_INFO); // Set log level to INFO (informational messages, warnings, and errors)

    // GPIO configuration
    gpio_reset_pin(LED_GPIO);                       // Reset the pin state
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); // Set it as output

    while (1)
    {
        ESP_LOGI(TAG, "LED ON");
        gpio_set_level(LED_GPIO, 1);                  // Turn on the LED
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS); // Delay 1 second

        ESP_LOGI(TAG, "LED OFF");
        gpio_set_level(LED_GPIO, 0);                  // Turn off the LED
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS); // Delay 1 second
    }
}