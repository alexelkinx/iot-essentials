#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/rmt.h"

#define GPIO_OUTPUT_IO_0 18
#define GPIO_OUTPUT_IO_1 19
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1))

#define GPIO_INPUT_IO_0 4
#define GPIO_INPUT_IO_1 5
#define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1))

// Additional GPIO pin for oscilloscope
#define GPIO_OUTPUT_IO_2 21
#define GPIO_OUTPUT_PIN_SEL_2 (1ULL << GPIO_OUTPUT_IO_2)

// RMT channel and GPIO for transmission
#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define RMT_TX_GPIO 23

#define ESP_INTR_FLAG_DEFAULT 0

static QueueHandle_t gpio_evt_queue = NULL;
volatile int a;

void printTaskList(void)
{
    char *taskListBuffer = malloc(1024);
    if (taskListBuffer == NULL)
    {
        printf("Failed to allocate memory for task list!");
        return;
    }
    vTaskList(taskListBuffer);
    printf("\nTask Name\tStatus\tPrio\tStack\tTask#\n%s", taskListBuffer);
    free(taskListBuffer);
}

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    gpio_set_level(GPIO_OUTPUT_IO_2, 1); // Set GPIO_OUTPUT_IO_2 to high
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}

void doWorkTask(void *arg)
{
    for (;;)
    {
        for (int i = 0; i < 10000; i++)
        {
            a = a + 3;
        }
        vTaskDelay(1);
    }
}

// Task to handle GPIO events
static void gpio_task(void *arg)
{
    uint32_t io_num;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
        {
            printf("GPIO[%" PRIu32 "] intr, val: %d\n", io_num, gpio_get_level(io_num));
            gpio_set_level(GPIO_OUTPUT_IO_2, 0); // Set GPIO_OUTPUT_IO_2 to low
        }
    }
}

// RMT sequence for signal generation
static const rmt_item32_t rmt_items[] = {
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 0, 32767, 0}}}, // SPACE
    // S : dot, dot, dot
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 0, 32767, 0}}}, // SPACE
    // P : dot, dash, dash, dot
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 1, 32767, 1}}},
    {{{32767, 1, 32767, 0}}}, // dash
    {{{32767, 1, 32767, 1}}},
    {{{32767, 1, 32767, 0}}}, // dash
    {{{32767, 1, 32767, 0}}}, // dot
    {{{32767, 0, 32767, 0}}}, // SPACE
    {{{32767, 0, 32767, 0}}}, // SPACE
    {{{32767, 0, 32767, 0}}}, // SPACE
    // RMT end marker
    {{{0, 1, 0, 0}}}};

static void rmt_tx_init(void)
{
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(RMT_TX_GPIO, RMT_TX_CHANNEL);
    config.tx_config.carrier_en = false;
    config.clk_div = 255;
    config.tx_config.loop_en = true;
    config.tx_config.loop_count = 0;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
}

void app_main(void)
{
    gpio_config_t io_conf = {};
    // Configure GPIOs as outputs
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL | GPIO_OUTPUT_PIN_SEL_2; // Include GPIO_OUTPUT_IO_2
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Configure GPIOs as inputs
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // Change gpio interrupt type for one pin
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

    // Create a queue to handle GPIO events
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // Start the GPIO task with priority 4
    xTaskCreate(gpio_task, "gpio_task", 2048, NULL, 4, NULL);

    // Start the high-priority work task with priority 9
    xTaskCreate(doWorkTask, "doWorkTask", 2048, NULL, 9, NULL);

    // Print the task list for debugging
    printTaskList();

    // Install GPIO ISR service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Hook ISR handler for specific GPIO pins
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void *)GPIO_INPUT_IO_0);
    gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void *)GPIO_INPUT_IO_1);

    // Initialize RMT
    rmt_tx_init();

    // Start RMT transmission with the defined sequence
    ESP_ERROR_CHECK(rmt_write_items(RMT_TX_CHANNEL, rmt_items, sizeof(rmt_items) / sizeof(rmt_items[0]), true));

    // main loop to toggle GPIO_OUTPUT_IO_0 and GPIO_OUTPUT_IO_1
    int cnt = 0;

    while (1)
    {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
        gpio_set_level(GPIO_OUTPUT_IO_1, cnt % 2);
    }
}
