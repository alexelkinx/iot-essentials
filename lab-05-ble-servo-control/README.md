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

# Lab 5: BLE Servo Control

## Project Overview

In **Lab 5**, I developed a **BLE-controlled servo motor system** using the ESP32 and ESP-IDF. The lab was divided into two projects:

1. A standalone servo tester using **MCPWM**
2. A BLE GATT server application that accepts servo angle values over Bluetooth and updates the servo accordingly

## Key Features:

- BLE-based servo control using characteristic write
- Uses FreeRTOS queue to transfer angle values from BLE handler to the servo task
- Separate MCPWM project demonstrates continuous angle sweeping from -90° to +90°
- Built with **CMake** and ESP-IDF

## Task Description

The task description can be found in the [task-description.md](task-description.md) file.

## Solution

The solution includes two ESP-IDF projects:

### `mcpwm_servo_control` directory:

- `main/mcpwm_servo_control.c`: Demonstrates smooth servo movement in a loop using MCPWM
- `main/servo.c` and `main/servo.h`: Initializes PWM and controls servo based on angle
- `CMakeLists.txt`: Build configuration

### `gatt_server_service_table` directory:

- `main/gatts_table_creat.c` and `gatts_table_creat.h`: Implements the BLE GATT server, including advertisement, GATT database, and write handling
- `main/servo.c` and `main/servo.h`: Same reusable servo control module as in the MCPWM example
- FreeRTOS queue used to decouple BLE events from PWM logic
- `CMakeLists.txt`: Build configuration

## How to Build and Run

1. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

2. Build and run the **MCPWM test app**:

   ```sh
   cd mcpwm_servo_control
   idf.py build
   idf.py flash
   idf.py monitor
   ```

3. Build and run the **BLE GATT server app**:

   ```sh
   cd ../gatt_server_service_table
   idf.py build
   idf.py flash
   idf.py monitor
   ```

4. Use a mobile app like **LightBlue** or **BLE Scanner** to connect to `ESP_GATTS_ALEX` and write an angle (e.g., `45`) to the appropriate characteristic.
