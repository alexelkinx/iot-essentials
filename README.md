# IoT Essentials

## Overview

This repository contains the projects and solutions for the **IoT Essentials** course, which covers key aspects of hardware and software integration, including GPIO control, traffic light systems, and the use of oscilloscopes. The course focuses on programming with the ESP-IDF framework, and each lab is designed to deepen the understanding of fundamental concepts such as state machines and hardware interaction.

The course includes several labs that involve the development of:

1. A **Blink + Hardware Tools** to demonstrate basic GPIO handling by blinking an LED.
2. A **Traffic Light System** that simulates traffic light operations with various states and timing sequences.
3. A **FreeRTOS Multitasking project** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies.
4. An **ISR Latency and RMT Interrupts lab** that measures GPIO interrupt latency and explores task responsiveness using synchronous and asynchronous interrupt triggering with the RMT peripheral.
5. A **BLE Servo Control project** that integrates a servo motor with a Bluetooth Low Energy GATT server for remote angle control.

## Table of Contents

- [Lab 1: Blink + Hardware Tools](#lab-1-blink--hardware-tools)
- [Lab 2: Traffic Light System](#lab-2-traffic-light-system)
- [Lab 3: FreeRTOS Multitasking](#lab-3-freertos-multitasking)
- [Lab 4: ISR Latency and RMT Interrupts](#lab-4-isr-latency-and-rmt-interrupts)
- [Lab 5: BLE Servo Control](#lab-5-ble-servo-control)
- [Building the Projects](#building-the-projects)

## Lab 1: Blink + Hardware Tools

### Project Overview

In **Lab 1**, I developed a simple **Blink application** using the ESP-IDF framework to blink an LED connected to a GPIO pin. This lab serves as an introduction to GPIO handling and the ESP-IDF build system.

### Key Features:

- Blinks an LED connected to GPIO 6
- Built with **CMake** for managing the build process

**[See Lab 1 Details](lab-01-blink-hw-tools/README.md)**

---

## Lab 2: Traffic Light System

### Project Overview

In **Lab 2**, I created a **Traffic Light System** that manages the states of a traffic light, including **RED**, **YELLOW**, **GREEN**, and special periods like **BLINKING YELLOW** during the night. The system uses a state machine to handle the transitions and timing sequences.

### Key Features:

- Simulates **traffic light state transitions**
- Handles **day and night periods** with different behaviors
- Built with **CMake** for managing the build process

**[See Lab 2 Details](lab-02-traffic-light/README.md)**

---

## Lab 3: FreeRTOS Multitasking

### Project Overview

In **Lab 3**, I developed a **FreeRTOS Multitasking application** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies. This lab covers the creation and management of multiple tasks in FreeRTOS.

### Key Features:

- Blinks three LEDs at different frequencies using FreeRTOS tasks
- Demonstrates multitasking and task scheduling in FreeRTOS
- Built with **CMake** for managing the build process

**[See Lab 3 Details](lab-03-freertos-multitasking/README.md)**

---

## Lab 4: ISR Latency and RMT Interrupts

### Project Overview

In **Lab 4**, I explored GPIO interrupt latency and task-level responsiveness using the ESP32 and FreeRTOS. This lab involved measuring ISR and task latencies under different scenarios, including context switching and asynchronous interrupt triggering with the RMT peripheral.

### Key Features:

- Measures latency from GPIO input event to ISR and task handler
- Implements context switching optimization in ISR
- Analyzes code-synchronous vs. asynchronous interrupt behavior
- Uses RMT peripheral to generate asynchronous GPIO signals
- Built with **CMake** for managing the build process

**[See Lab 4 Details](lab-04-isr-latency-rmt/README.md)**

---

## Lab 5: BLE Servo Control

### Project Overview

In **Lab 5**, I implemented a **BLE-controlled servo motor system** using the ESP32 and ESP-IDF. The lab involved controlling a servo motor over Bluetooth by integrating FreeRTOS multitasking, PWM with MCPWM, and a GATT server BLE application.

### Key Features:

- Controls servo motor angle via BLE characteristic write
- Refactors PWM functionality into a reusable `servo.c` module
- Uses FreeRTOS queue to communicate between BLE callback and main task
- Built with **CMake** and ESP-IDF

**[See Lab 5 Details](lab-05-ble-servo-control/README.md)**

---

## Building the Projects

### Prerequisites

- ESP-IDF framework
- CMake
- A compatible ESP32 development board

### Building and Running Individual Labs

Each lab folder contains its own `README.md` file with instructions for building, flashing, and monitoring.  
Please refer to those files for lab-specific steps using the ESP-IDF toolchain.

---

Feel free to explore each lab's folder for more detailed documentation and source code.
