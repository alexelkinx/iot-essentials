#ifndef GPIO_LIGHTS_H
#define GPIO_LIGHTS_H

#include "traffic_light_logic.h"

void init_lights(void);
void set_lights(traffic_color_t color);

#endif // GPIO_LIGHTS_H