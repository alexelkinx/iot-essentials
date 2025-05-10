# IoT Essentials

<p align="center">
  <img src="https://img.shields.io/badge/Framework-ESP--IDF-blue" alt="ESP-IDF"/>
  <img src="https://img.shields.io/badge/Build-CMake-informational" alt="CMake"/>
  <img src="https://img.shields.io/badge/RTOS-FreeRTOS-blueviolet" alt="FreeRTOS"/>
  <img src="https://img.shields.io/badge/Hardware-GPIO-green" alt="GPIO"/>
  <img src="https://img.shields.io/badge/Hardware-PWM-green" alt="PWM"/>
  <img src="https://img.shields.io/badge/Wireless-BLE-lightblue" alt="BLE"/>
  <img src="https://img.shields.io/badge/Protocol-MQTT-yellow" alt="MQTT"/>
  <img src="https://img.shields.io/badge/Platform-Docker-blue" alt="Docker"/>
  <img src="https://img.shields.io/badge/Tool-Node--RED-red" alt="Node-RED"/>
  <img src="https://img.shields.io/badge/Database-InfluxDB-lightblue" alt="InfluxDB"/>
  <img src="https://img.shields.io/badge/Visualization-Grafana-orange" alt="Grafana"/>
  <img src="https://img.shields.io/badge/Sensor-RuuviTag-success" alt="RuuviTag"/>
  <img src="https://img.shields.io/badge/Script-Python-yellowgreen" alt="Python"/>
  <img src="https://img.shields.io/badge/Manager-Portainer-blue" alt="Portainer"/>
</p>

## Overview

This repository contains the projects and solutions for the **IoT Essentials** course, which covers key aspects of hardware and software integration, including GPIO control, traffic light systems, and the use of oscilloscopes. The course focuses on programming with the ESP-IDF framework, and each lab is designed to deepen the understanding of fundamental concepts such as state machines and hardware interaction.

The course includes several labs that involve the development of:

1. A **Blink + Hardware Tools** to demonstrate basic GPIO handling by blinking an LED.
2. A **Traffic Light System** that simulates traffic light operations with various states and timing sequences.
3. A **FreeRTOS Multitasking project** that demonstrates multitasking with FreeRTOS by blinking multiple LEDs at different frequencies.
4. An **ISR Latency and RMT Interrupts lab** that measures GPIO interrupt latency and explores task responsiveness using synchronous and asynchronous interrupt triggering with the RMT peripheral.
5. A **BLE Servo Control project** that integrates a servo motor with a Bluetooth Low Energy GATT server for remote angle control.
6. An **MQTT Servo and Blink Control project** that demonstrates remote control of a servo motor and LED blink rate via MQTT topics.
7. An **IoT Stack Integration lab** that connects sensor data sources (e.g. RuuviTag) to a full Docker-based IoT stack including MQTT, Node-RED, InfluxDB, and Grafana for data processing and visualization.

## Table of Contents

- [Lab 1: Blink + Hardware Tools](#lab-1-blink--hardware-tools)
- [Lab 2: Traffic Light System](#lab-2-traffic-light-system)
- [Lab 3: FreeRTOS Multitasking](#lab-3-freertos-multitasking)
- [Lab 4: ISR Latency and RMT Interrupts](#lab-4-isr-latency-and-rmt-interrupts)
- [Lab 5: BLE Servo Control](#lab-5-ble-servo-control)
- [Lab 6: MQTT Servo and Blink Control](#lab-6-mqtt-servo-and-blink-control)
- [Lab 7: IoT Stack Integration](#lab-7-iot-stack-integration)
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

In **Lab 5**, I developed a **BLE-controlled servo motor system** using the ESP32 and ESP-IDF. The lab is split into two separate projects:

- A standalone MCPWM example that continuously sweeps the servo angle
- A BLE GATT server that receives angle values via characteristic write and updates the servo in real time

### Key Features:

- BLE-based servo control using characteristic write
- Uses FreeRTOS queue to transfer angle values from BLE handler to the servo task
- Separate MCPWM project demonstrates continuous angle sweeping from -90° to +90°
- Built with **CMake** and ESP-IDF

**[See Lab 5 Details](lab-05-ble-servo-control/README.md)**

---

## Lab 6: MQTT Servo and Blink Control

### Project Overview

In **Lab 6**, I implemented an **MQTT-controlled system** to manage a servo motor and an LED blink rate using the ESP32 and ESP-IDF. This lab extends the servo functionality from Lab 5 and integrates Wi-Fi and MQTT communication for remote control.

### Key Features:

- Subscribes to two MQTT topics: one for LED blink rate and one for servo angle
- Uses FreeRTOS queues to decouple MQTT event handling from task logic
- Servo control is built on a reusable `servo.c` module from Lab 5
- Blink task uses timeout logic to toggle LED if no updates are received
- Built with **CMake** and ESP-IDF

**[See Lab 6 Details](lab-06-mqtt-servo-blink/README.md)**

---

## Lab 7: IoT Stack Integration

### Project Overview

In **Lab 7**, I integrated a complete **Docker-based IoT stack** on a Raspberry Pi to collect, store, and visualize sensor data. The lab demonstrates how to combine multiple containerized services for a real-world sensor-to-dashboard pipeline using RuuviTags and ESP32.

### Key Features:

- Dockerized setup including **Mosquitto**, **Node-RED**, **InfluxDB**, **Grafana**, and **Portainer-CE**
- Uses **MQTT Simulator** and **RuuviTag listener script** to publish sensor data
- Node-RED processes incoming MQTT messages and stores them into InfluxDB
- Grafana visualizes time-series data from InfluxDB
- ESP32 receives control messages (e.g., LED toggle) based on sensor values
- Built on Raspberry Pi with ESP-IDF-based firmware for ESP32

**[See Lab 7 Details](lab-07-iot-stack-integration/README.md)**

## Building the Projects

### Prerequisites

- [ESP-IDF framework](https://github.com/espressif/esp-idf)
- [CMake](https://cmake.org/)
- A compatible ESP32 development board

### Building and Running Individual Labs

Each lab folder contains its own `README.md` file with instructions for building, flashing, and monitoring.  
Please refer to those files for lab-specific steps using the ESP-IDF toolchain.

---

Feel free to explore each lab's folder for more detailed documentation and source code.
