#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "mqtt_client.h"
#include "nvs_flash.h"
#include "servo.h"
#include "blink.h"

static const char *TAG = "mqtt_lab";
static esp_mqtt_client_handle_t client; // MQTT client instance

static QueueHandle_t mqtt_msg_queue = NULL; // Queue for all incoming MQTT messages
QueueHandle_t servo_queue = NULL;           // Queue for servo angle values
QueueHandle_t blink_queue = NULL;           // Queue for LED blink delay values

// MQTT message format
typedef struct
{
    char topic[64];
    char data[128];
} mqtt_msg_t;

// Handles incoming MQTT messages and sends them to queues
static void mqtt_process_task(void *pvParameters)
{
    mqtt_msg_t msg;
    while (1)
    {
        // Wait for new MQTT message from the queue
        if (xQueueReceive(mqtt_msg_queue, &msg, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "Topic: %s", msg.topic);
            ESP_LOGI(TAG, "Data: %s", msg.data);

            if (strncmp(msg.topic, "/esp32c6/servo_angle", strlen("/esp32c6/servo_angle")) == 0)
            {
                char *endptr;
                int angle = strtol(msg.data, &endptr, 10);
                if (*endptr != '\0')
                {
                    ESP_LOGW(TAG, "Invalid servo angle: not a number");
                    continue;
                }
                // Convert string to int and send to servo_queue
                xQueueSend(servo_queue, &angle, portMAX_DELAY);
            }
            else if (strncmp(msg.topic, "/esp32c6/blink_rate", strlen("/esp32c6/blink_rate")) == 0)
            {
                char *endptr;
                int delay_ms = strtol(msg.data, &endptr, 10);
                if (*endptr != '\0' || delay_ms <= 0)
                {
                    ESP_LOGW(TAG, "Invalid blink delay: not a positive number");
                    continue;
                }
                // Convert string to int and send to blink_queue
                xQueueSend(blink_queue, &delay_ms, portMAX_DELAY);
            }
        }
    }
}

// MQTT event handler
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "Connected to broker");
        // Subscribe to required MQTT topics will also receive messages published to these topics
        esp_mqtt_client_subscribe(client, "/esp32c6/qos0", 0);
        esp_mqtt_client_subscribe(client, "/esp32c6/servo_angle", 0);
        esp_mqtt_client_subscribe(client, "/esp32c6/blink_rate", 0);
        break;

    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "Received data");
        mqtt_msg_t msg;
        memset(&msg, 0, sizeof(mqtt_msg_t));

        // Parse incoming topic and payload into mqtt_msg_t structure
        snprintf(msg.topic, sizeof(msg.topic), "%.*s", event->topic_len, event->topic);
        snprintf(msg.data, sizeof(msg.data), "%.*s", event->data_len, event->data);

        // Send message to mqtt_msg_queue
        if (xQueueSend(mqtt_msg_queue, &msg, portMAX_DELAY) != pdPASS)
            break;
    default:
        break;
    }
}

// Initialize MQTT client
static void mqtt_init(void)
{
    // Set MQTT broker URI
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://mqtt.eclipseprojects.io"};
    // Create client with config
    client = esp_mqtt_client_init(&mqtt_cfg);
    // Register event handler for all MQTT events
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    // Start the client
    esp_mqtt_client_start(client);
}

// Handle Wi-Fi and IP events
static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect(); // Try to connect to Wi-Fi
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        mqtt_init(); // Start MQTT client once Wi-Fi is connected
    }
}

// Function to configure Wi-Fi
static void wifi_init(void)
{
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Register event handlers for Wi-Fi and IP events
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "EMBO-Lab",
            .password = "embl4b#Lab",
        },
    };

    // Set Wi-Fi credentials and start in station mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void app_main(void)
{
    // Set log levels
    esp_log_level_set("*", ESP_LOG_WARN);          // Default
    esp_log_level_set("wifi", ESP_LOG_ERROR);      // Wi-Fi
    esp_log_level_set("mqtt_lab", ESP_LOG_INFO);   // MQTT
    esp_log_level_set("servo_task", ESP_LOG_INFO); // Servo
    esp_log_level_set("blink_task", ESP_LOG_INFO); // Blink

    // Initialize NVS, network interface, and event loop
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init(); // Initialize Wi-Fi

    // Create queues for MQTT message processing and task communication
    mqtt_msg_queue = xQueueCreate(10, sizeof(mqtt_msg_t));
    servo_queue = xQueueCreate(10, sizeof(int));
    blink_queue = xQueueCreate(10, sizeof(int));

    init_servo(); // Initialize servo

    // Launch tasks with appropriate priorities
    xTaskCreate(&mqtt_process_task, "mqtt_process_task", 4096, NULL, 5, NULL);
    xTaskCreate(&servo_task, "servo_task", 4096, NULL, 4, NULL);
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 3, NULL);
}