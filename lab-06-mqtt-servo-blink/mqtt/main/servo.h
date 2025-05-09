#ifndef SERVO_H
#define SERVO_H

void init_servo(void);
void set_angle(int angle);
void servo_task(void *pvParameters);

#endif // SERVO_H