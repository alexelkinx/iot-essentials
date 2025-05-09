#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "blink.h"
#include <inttypes.h> // For PRIu32

#define BLINK_GPIO GPIO_NUM_2 // GPIO for the LED

static const char *TAG = "blink_task";
extern QueueHandle_t blink_queue;

void blink_task(void *pvParameters)
{
    int new_delay;
    uint32_t default_delay_ms = 1000; // Default delay (1 second)

    // Init GPIO as output
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1)
    {
        // Wait for new delay (timeout = current delay)
        if (xQueueReceive(blink_queue, &new_delay, default_delay_ms / portTICK_PERIOD_MS))
        {
            ESP_LOGI(TAG, "Received new delay: %d ms", new_delay);
            default_delay_ms = new_delay;
        }

        // Toggle LED ON
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(default_delay_ms / portTICK_PERIOD_MS);

        // Toggle LED OFF
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(default_delay_ms / portTICK_PERIOD_MS);
    }
}