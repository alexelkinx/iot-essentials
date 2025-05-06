#include "servo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    ESP_LOGI("Main", "Starting servo control example");

    init_servo();

    int angle = 0; // Start at 0 degrees
    int step = 2;  // Move in 2-degree steps

    while (1)
    {
        ESP_LOGI("Main", "Angle of rotation: %d", angle);
        set_angle(angle);
        vTaskDelay(pdMS_TO_TICKS(100));

        if (angle == 90)
        {
            step = -2; // Once it reaches +90°, start moving down
        }
        else if (angle == -90)
        {
            step = 2; // Once it reaches -90°, start moving up
        }
        angle += step;
    }
}