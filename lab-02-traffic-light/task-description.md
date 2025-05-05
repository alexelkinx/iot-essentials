# Lab 2 GPIO

## Assignment

Using red, yellow and green LEDs, create a traffic light. Requirements specification:

- Between 06:00 to 22:00 the light shall follow Finnish sequence red - red+yellow - green - yellow. Choose appropriate timing for demonstration.
- Between 22:00 - 06:00 there shall be blinking yellow.
- The program shall have modular structure as follows
  - `traffic_light_logic.c` contains the core logic **without any timing or GPIO handling**, with rationale that this allows testing the code at arbitrary speed, possibly on another architecture testing CPU. Especially this part you can generate by AI (request a nice clear maintainable state machine implementation). The module interface functions are
    `traffic_color_t set_time(unsigned char hours, unsigned char minutes, unsigned char seconds)` that will set the module internal time and return color enum of the five possible states of lights (it is allowed to start always with red state or blink state after setting the time), and
    `traffic_color_t next_second(void)` that returns the light color of after advancing module internal time by second.
    Implement `traffic_light_logic.h` with function prototypes and enum, and `#include that in main code.
    - `gpio_lights.c` contains functions
      `void init_lights(void)` that sets the selected GPIO pins as outputs,
      `void set_lights(traffic_color_t color)` that sets the GPIO states as requested.
- For demonstration, set time to 05:59 to see that the transition from yellow blinks to normal sequence works as expected.

You can use blink example as starting point.
