#include "gpio_lights.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define RED_LED_GPIO GPIO_NUM_4
#define YELLOW_LED_GPIO GPIO_NUM_5
#define GREEN_LED_GPIO GPIO_NUM_6

static const char *TAG = "GPIO_LIGHTS";

void init_lights(void)
{
    gpio_reset_pin(RED_LED_GPIO);
    gpio_set_direction(RED_LED_GPIO, GPIO_MODE_OUTPUT);
    ESP_LOGI(TAG, "Initialized RED LED on GPIO %d", RED_LED_GPIO);

    gpio_reset_pin(YELLOW_LED_GPIO);
    gpio_set_direction(YELLOW_LED_GPIO, GPIO_MODE_OUTPUT);
    ESP_LOGI(TAG, "Initialized YELLOW LED on GPIO %d", YELLOW_LED_GPIO);

    gpio_reset_pin(GREEN_LED_GPIO);
    gpio_set_direction(GREEN_LED_GPIO, GPIO_MODE_OUTPUT);
    ESP_LOGI(TAG, "Initialized GREEN LED on GPIO %d", GREEN_LED_GPIO);
}

void set_lights(traffic_color_t color)
{
    switch (color)
    {
    case RED:
        gpio_set_level(RED_LED_GPIO, 1);
        gpio_set_level(YELLOW_LED_GPIO, 0);
        gpio_set_level(GREEN_LED_GPIO, 0);
        ESP_LOGI(TAG, "Set lights: RED");
        break;
    case RED_YELLOW:
        gpio_set_level(RED_LED_GPIO, 1);
        gpio_set_level(YELLOW_LED_GPIO, 1);
        gpio_set_level(GREEN_LED_GPIO, 0);
        ESP_LOGI(TAG, "Set lights: RED + YELLOW");
        break;
    case GREEN:
        gpio_set_level(RED_LED_GPIO, 0);
        gpio_set_level(YELLOW_LED_GPIO, 0);
        gpio_set_level(GREEN_LED_GPIO, 1);
        ESP_LOGI(TAG, "Set lights: GREEN");
        break;
    case YELLOW:
        gpio_set_level(RED_LED_GPIO, 0);
        gpio_set_level(YELLOW_LED_GPIO, 1);
        gpio_set_level(GREEN_LED_GPIO, 0);
        ESP_LOGI(TAG, "Set lights: YELLOW");
        break;
    case BLINK_YELLOW:
        gpio_set_level(RED_LED_GPIO, 0);
        gpio_set_level(YELLOW_LED_GPIO, !gpio_get_level(YELLOW_LED_GPIO));
        gpio_set_level(GREEN_LED_GPIO, 0);
        ESP_LOGI(TAG, "Set lights: BLINK YELLOW");
        break;
    }
}