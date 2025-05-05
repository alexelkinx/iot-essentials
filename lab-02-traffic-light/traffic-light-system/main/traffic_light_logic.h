#ifndef TRAFFIC_LIGHT_LOGIC_H
#define TRAFFIC_LIGHT_LOGIC_H

typedef enum
{
    RED,
    RED_YELLOW,
    GREEN,
    YELLOW,
    BLINK_YELLOW
} traffic_color_t;

traffic_color_t set_time(unsigned char hours, unsigned char minutes, unsigned char seconds);
traffic_color_t next_second(void);

#endif // TRAFFIC_LIGHT_LOGIC_H