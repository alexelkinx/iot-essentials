# Lab 6 MQTT

MQTT is common protocol that binds IoT devices together. It is based on publish-subscribe model, where **publisher**s send data to **topic**s on a **broker**, and **subscriber**s will get updates as new data is published.

In this lab you will

- study ESP32 MQTT example
- integrate that example to LED blink and servo controls

![alt text](assets/MQTT_Diagram_gOmDdU4.png)

## 6.1 MQTT example

### 6.1.1 Running the example

In ESP32 examples, create a copy of mqtt / tcp example. TCP here means that the example has no encryption or authentication, it is just plain mqtt on tcp (we will look at security issues on IoT security course).

Configure the project

- emblab wifi SSID: `EMBO-Lab`
- emblab wifi passwd = `embl4b#Lab`

After configuration the example is plug and play. It connects to a test broker `mqtt://mqtt.eclipseprojects.io` so you will see the messages from other students and maybe from everywhere in the world running the same example with default topic.

Publish some example messages to the topics the device is subscribed to (`/topic/qos0`) and check that you receive those. You can use Android app "MyMQTT" or any web online client.

### 6.1.2 The anatomy of the app

The example code demonstrates publishing data directly from mqtt event handler when connection to broker is established.

As in previous BLE lab, start with adding the necessary code snippets and checking out

1. What are the wifi/mqtt stack tasks running at what priorities?
2. What task context is the callback running?

Again, the safest approach will be to **create a queue for event messages and handle them in lower priority application task**.

## 6.2. Modify the MQTT example

You will want to control one led blink task and one servo control task via MQTT, so the app should subscribe to two topics.

- In mqtt event handler, subscribe to topics `/<your_random_string>/blink_rate` and `/<your_random_string>/servo_angle`
- Create a queue for each event
- In MQTT_EVENT_DATA event, check which topic that was and send the data to queue
- Create additional tasks at low priorities:
  - Servo task waits for message and sets the angle accordingly (you have the servo module from previous lab)
  - Blink task waits for updated delay **with timeout equal to blink rate**: so if there is no message, then led will be toggled after timeout; if there is a message, then timeout will be updated.
