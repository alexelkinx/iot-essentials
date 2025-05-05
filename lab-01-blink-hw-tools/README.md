# Lab 1: Blink + Hardware Tools

This lab demonstrates a simple example of blinking an LED using the ESP-IDF framework.

## Task Description

The task description can be found in the [task-description.md](task-description.md) file.

## Solution

The solution files are located in the `blink` directory.

- `blink/blink.c`: Contains the main application code to blink an LED connected to GPIO 6.
- `blink/CMakeLists.txt`: CMake configuration for the blink example.

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build the project:

   ```sh
   cd blink
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
