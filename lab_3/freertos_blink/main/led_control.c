#include "led_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "LED_CONTROL"

// Define LED pins
#define RED_LED GPIO_NUM_4
#define YELLOW_LED GPIO_NUM_5
#define GREEN_LED GPIO_NUM_6

// Convert frequency (Hz) to delay (milliseconds)
#define FREQ_TO_DELAY(freq) (1000 / (freq * 2))

// LED configurations
led_t leds[] = {
    {RED_LED, "RED", 3},
    {YELLOW_LED, "YELLOW", 7},
    {GREEN_LED, "GREEN", 11}};

// Initialize LED GPIOs
void init_leds(void)
{
    for (int i = 0; i < 3; i++)
    {
        gpio_reset_pin(leds[i].gpio);
        gpio_set_direction(leds[i].gpio, GPIO_MODE_OUTPUT);
    }
}

// Task function to blink LEDs
void blink_led_task(void *arg)
{
    led_t *led = (led_t *)arg;
    int delay_time = FREQ_TO_DELAY(led->frequency);

    while (1)
    {
        gpio_set_level(led->gpio, 1);
        vTaskDelay(pdMS_TO_TICKS(delay_time));
        gpio_set_level(led->gpio, 0);
        vTaskDelay(pdMS_TO_TICKS(delay_time));
    }
}

// Task function to log LED status every 5 seconds
void log_status_task(void *arg)
{
    static char task_stats[1024]; // Buffer for task stats

    while (1)
    {
        vTaskGetRunTimeStats(task_stats);
        ESP_LOGI("TASK_STATS", "\nTask Runtime Stats:\n%s", task_stats);
        vTaskDelay(pdMS_TO_TICKS(5000)); // Log every 5 seconds
    }
}