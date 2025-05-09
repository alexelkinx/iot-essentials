# Lab 6: MQTT Servo and Blink Control

## Project Overview

In **Lab 6**, I implemented an **MQTT-controlled system** using the ESP32 and ESP-IDF to manage a servo motor and an LED blink rate. The system subscribes to two MQTT topics and reacts in real time using FreeRTOS tasks and queues. This lab builds upon the servo module from Lab 5 and demonstrates MQTT-based control over Wi-Fi.

## Key Features:

- Controls LED blink rate and servo motor angle via MQTT topics
- Subscribes to `/esp32c6/blink_rate` and `/esp32c6/servo_angle`
- Uses FreeRTOS queues for decoupled task communication
- Implements timeout-based LED blinking when no MQTT update is received
- Built with **CMake** and ESP-IDF

## Task Description

The task description can be found in the [task-description.md](task-description.md) file.

## Solution

The solution is implemented in the `mqtt/` directory and consists of:

- `main/app_main.c`: Initializes Wi-Fi and MQTT, creates FreeRTOS tasks, handles MQTT events
- `main/blink.c` and `main/blink.h`: Implements an LED blinking task with dynamic delay
- `main/servo.c` and `main/servo.h`: Reusable servo control module based on MCPWM, listens to queue for angle updates
- `CMakeLists.txt`: Project-level build configuration

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build the project:

   ```sh
   cd lab-06-mqtt-servo-blink/mqtt
   idf.py build
   ```

3. Flash the firmware to the ESP32 board:

   ```sh
   idf.py flash
   ```

4. Monitor the serial output:

   ```sh
   idf.py monitor
   ```

5. Use an MQTT client such as **MQTTX**, **MyMQTT**, or **MQTT Explorer** to publish to:

   - `/esp32c6/blink_rate`: integer delay in milliseconds (e.g., `500`)
   - `/esp32c6/servo_angle`: integer angle between -90 and 90 (e.g., `45`)
