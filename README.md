# IoT Essentials Labs

## Overview

This repository contains the projects and solutions for the **IoT Essentials Labs** course, which covers various aspects of hardware and software integration, including GPIO handling, traffic light systems, and using oscilloscopes. The course focuses on programming with the ESP-IDF framework, and each lab is designed to strengthen the understanding of fundamental concepts such as GPIO control, state machines, and hardware interaction.

The course includes several labs that involve the development of:

1. A **Blink Example** to demonstrate basic GPIO handling by blinking an LED.
2. A **Traffic Light System** that simulates traffic light operations with various states and timing sequences.
3. A **FreeRTOS Multitasking Example** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies.

## Table of Contents

- [Lab 1: Blink Example](#lab-1-blink-example)
- [Lab 2: Traffic Light System](#lab-2-traffic-light-system)
- [Lab 3: FreeRTOS Multitasking Example](#lab-3-freertos-multitasking-example)
- [Building the Projects](#building-the-projects)

## Lab 1: Blink Example

### Project Overview

In **Lab 1**, I developed a simple **Blink Example** application using the ESP-IDF framework to blink an LED connected to a GPIO pin. This lab serves as an introduction to GPIO handling and the ESP-IDF build system.

### Key Features:

- Blinks an LED connected to GPIO 6
- Built with **CMake** for managing the build process

**[See Lab 1 Details](lab_1/README.md)**

---

## Lab 2: Traffic Light System

### Project Overview

In **Lab 2**, I created a **Traffic Light System** that manages the states of a traffic light, including **RED**, **YELLOW**, **GREEN**, and special periods like **BLINKING YELLOW** during the night. The system uses a state machine to handle the transitions and timing sequences.

### Key Features:

- Simulates **traffic light state transitions**
- Handles **day and night periods** with different behaviors
- Built with **CMake** for managing the build process

**[See Lab 2 Details](lab_2/README.md)**

---

## Lab 3: FreeRTOS Multitasking Example

### Project Overview

In **Lab 3**, I developed a **FreeRTOS Multitasking Example** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies. This lab covers the creation and management of multiple tasks in FreeRTOS.

### Key Features:

- Blinks three LEDs at different frequencies using FreeRTOS tasks
- Demonstrates multitasking and task scheduling in FreeRTOS
- Built with **CMake** for managing the build process

**[See Lab 3 Details](lab_3/README.md)**

---

## Building the Projects

### Prerequisites

- ESP-IDF framework
- CMake
- A compatible ESP32 development board

### Building the Projects

1. Clone the repository:

   ```sh
   git clone <repository-url>
   cd <repository-directory>
   ```

2. Set up the ESP-IDF environment:

   ```sh
   . $HOME/esp/esp-idf/export.sh
   ```

3. Build the blink example:

   ```sh
   cd lab_1/blink
   idf.py build
   ```

4. Build the traffic light system:

   ```sh
   cd lab_2/traffic-light-system
   idf.py build
   ```

5. Build the FreeRTOS multitasking example:

   ```sh
   cd lab_3/freertos_blink
   idf.py build
   ```

### Flashing and Monitoring

1. Flash the firmware to the ESP32 board:

   ```sh
   idf.py flash
   ```

2. Monitor the serial output:

   ```sh
   idf.py monitor
   ```

---

Feel free to explore each lab's folder for more detailed documentation and source code.
