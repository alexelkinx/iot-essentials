#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm_prelude.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "servo.h"
#include <inttypes.h>

static const char *TAG = "servo_task";
extern QueueHandle_t servo_queue;

// Servo control parameters
#define SERVO_MIN_PULSEWIDTH_US 1000 // Minimum pulse width, 1.0 ms (-90°)
#define SERVO_MAX_PULSEWIDTH_US 2000 // Maximum pulse width, 2.0 ms (+90°)
#define SERVO_MIN_DEGREE -90         // Minimum servo angle
#define SERVO_MAX_DEGREE 90          // Maximum servo angle

#define SERVO_PULSE_GPIO 0 // GPIO pin for PWM output

#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000 // 1 MHz (1 µs per tick)
#define SERVO_TIMEBASE_PERIOD 20000          // 20000 ticks = 20 ms (50Hz PWM frequency)

static mcpwm_cmpr_handle_t comparator = NULL;

// Convert servo angle to corresponding PWM pulse width
static inline uint32_t servo_angle_to_pulsewidth(int angle)
{
    return (angle - SERVO_MIN_DEGREE) *
               (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) /
               (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) +
           SERVO_MIN_PULSEWIDTH_US;
}

void init_servo(void)
{
    ESP_LOGI(TAG, "Create timer and operator");
    mcpwm_timer_handle_t timer = NULL;
    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    mcpwm_oper_handle_t oper = NULL;
    mcpwm_operator_config_t operator_config = {
        .group_id = 0,
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

    ESP_LOGI(TAG, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    ESP_LOGI(TAG, "Create comparator and generator from the operator");
    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    mcpwm_gen_handle_t generator = NULL;
    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, servo_angle_to_pulsewidth(0)));

    ESP_LOGI(TAG, "Set generator action on timer and compare event");
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

    ESP_LOGI(TAG, "Servo initialized successfully");
}

void set_angle(int angle)
{
    uint32_t pulse_width = servo_angle_to_pulsewidth(angle);
    ESP_LOGI(TAG, "Setting servo angle: %d (Pulse width: %" PRIu32 "us)", angle, pulse_width);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, pulse_width));
}

// Task to handle messages for servo control
void servo_task(void *pvParameters)
{
    int new_angle;
    while (1)
    {
        // Wait for a message on the servo queue
        if (xQueueReceive(servo_queue, &new_angle, portMAX_DELAY))
        {
            if (new_angle >= SERVO_MIN_DEGREE && new_angle <= SERVO_MAX_DEGREE)
            {
                set_angle(new_angle);
            }
            else
            {
                ESP_LOGW(TAG, "Received invalid angle: %d", new_angle);
            }
        }
    }
}