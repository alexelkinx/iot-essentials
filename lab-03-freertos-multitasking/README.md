# Lab 3: FreeRTOS Multitasking

## Project Overview

In **Lab 3**, I developed a **FreeRTOS Multitasking Example** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies. This lab covers the creation and management of multiple tasks in FreeRTOS.

## Key Features:

- Blinks three LEDs at different frequencies using FreeRTOS tasks
- Demonstrates multitasking and task scheduling in FreeRTOS
- Built with **CMake** for managing the build process

## Task Description

The task description can be found in the [task_description.md](task_description.md) file.

## Solution

The solution files are located in the `freertos_blink` directory.

- `freertos_blink/main.c`: Contains the main application code.
- `freertos_blink/CMakeLists.txt`: CMake configuration for the FreeRTOS multitasking example.

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build the project:

   ```sh
   cd freertos_blink
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
