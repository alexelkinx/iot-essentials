#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "driver/gpio.h"

// Structure to store LED information
typedef struct
{
    int gpio;
    const char *color;
    int frequency;
} led_t;

// Declare LED array globally for access in app_main.c
extern led_t leds[3];

// Function declarations
void init_leds(void);
void blink_led_task(void *arg);
void log_status_task(void *arg);

#endif // LED_CONTROL_H
