# Lab 4: ISR Latency and RMT Interrupts

## Project Overview

In **Lab 4**, I studied **interrupt handling and task latency** on the ESP32 platform using GPIO and RMT peripherals. The lab focuses on measuring the delay from an external signal to ISR activation and task execution, exploring different configurations including immediate context switching and asynchronous triggering.

## Key Features:

- Measures latency from GPIO event to ISR and task handler
- Uses FreeRTOS queue between ISR and task
- Enables immediate context switching from ISR
- Generates interrupts asynchronously using RMT peripheral
- Built with **CMake** and ESP-IDF

## Task Description

The task description can be found in the [task-description.md](task-description.md) file.

## Solution

The solution consists of two main components located in separate directories:

### `generic-gpio` directory:

- `main/app_main.c`: Main code for GPIO input, ISR, and task-level latency measurement.
- `main/CMakeLists.txt`: CMake configuration for the GPIO-based application.
- `CMakeLists.txt`: Project-level CMake configuration.

### `morce` directory:

- `main/morce.c`: RMT-based pulse generator to simulate external asynchronous interrupts.
- `main/CMakeLists.txt`: CMake config for the RMT app.
- `CMakeLists.txt`: Project-level config.

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build and flash the `generic-gpio` application:

   ```sh
   cd generic-gpio
   idf.py build
   idf.py flash
   idf.py monitor
   ```

3. In a separate ESP32 device (or project), build and flash the `morce` application:

   ```sh
   cd ../morce
   idf.py build
   idf.py flash
   idf.py monitor
   ```

4. Use an oscilloscope to measure timing between input events and output changes as described in the task.
