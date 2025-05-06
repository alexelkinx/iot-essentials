# Lab 5: BLE Servo Control

## Project Overview

In **Lab 5**, I implemented a **BLE-controlled servo motor system** using the ESP32 and ESP-IDF. The lab involved controlling a servo motor over Bluetooth by integrating FreeRTOS multitasking, PWM with MCPWM, and a GATT server BLE application.

## Key Features:

- Controls servo motor angle via BLE characteristic write
- Refactors PWM functionality into a reusable `servo.c` module
- Uses FreeRTOS queue to communicate between BLE callback and main task
- Built with **CMake** and ESP-IDF

## Task Description

The task description can be found in the [task-description.md](task-description.md) file.

## Solution

The solution is organized in a single ESP-IDF project directory containing:

- `main/servo.c` and `main/servo.h`: Reusable module to initialize and control servo angle
- `main/app_main.c`: Main application code integrating BLE GATT server and servo control
- `CMakeLists.txt`: Project build configuration

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build the project:

   ```sh
   cd lab-05-ble-servo-control
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

5. Use a mobile app like **BLE Scanner** to connect and write to the servo angle characteristic.
