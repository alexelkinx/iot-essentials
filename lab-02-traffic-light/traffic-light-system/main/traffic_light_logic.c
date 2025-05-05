#include "traffic_light_logic.h"

static unsigned char current_hours;
static unsigned char current_minutes;
static unsigned char current_seconds;
static traffic_color_t current_color;

traffic_color_t set_time(unsigned char hours, unsigned char minutes, unsigned char seconds)
{
    current_hours = hours;
    current_minutes = minutes;
    current_seconds = seconds;

    if (hours >= 6 && hours < 22)
    {
        current_color = RED;
    }
    else
    {
        current_color = BLINK_YELLOW;
    }

    return current_color;
}

traffic_color_t next_second(void)
{
    current_seconds++;
    if (current_seconds >= 60)
    {
        current_seconds = 0;
        current_minutes++;
        if (current_minutes >= 60)
        {
            current_minutes = 0;
            current_hours++;
            if (current_hours >= 24)
            {
                current_hours = 0;
            }
        }
    }

    if (current_hours >= 6 && current_hours < 22)
    {
        switch (current_color)
        {
        case RED:
            current_color = RED_YELLOW;
            break;
        case RED_YELLOW:
            current_color = GREEN;
            break;
        case GREEN:
            current_color = YELLOW;
            break;
        case YELLOW:
            current_color = RED;
            break;
        default:
            current_color = RED;
            break;
        }
    }
    else
    {
        current_color = BLINK_YELLOW;
    }

    return current_color;
}