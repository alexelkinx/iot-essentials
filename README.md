# IoT Essentials Labs

## Overview

This repository contains the projects and solutions for the **IoT Essentials Labs** course, which covers various aspects of hardware and software integration, including GPIO handling, traffic light systems, and using oscilloscopes. The course focuses on programming with the ESP-IDF framework, and each lab is designed to strengthen the understanding of fundamental concepts such as GPIO control, state machines, and hardware interaction.

The course includes several labs that involve the development of:

1. A **Blink Example** to demonstrate basic GPIO handling by blinking an LED.

## Table of Contents

- [Lab 1: Blink Example](#lab-1-blink-example)
- [Building the Projects](#building-the-projects)

## Lab 1: Blink Example

### Project Overview

In **Lab 1**, I developed a simple **Blink Example** application using the ESP-IDF framework to blink an LED connected to a GPIO pin. This lab serves as an introduction to GPIO handling and the ESP-IDF build system.

### Key Features:

- Blinks an LED connected to GPIO 6
- Built with **CMake** for managing the build process

**[See Lab 1 Details](lab_1/README.md)**

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
