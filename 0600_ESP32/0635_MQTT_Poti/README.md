# ESP32 with LED and Poti, Python Scripts as the Counterparts #

The project demonstrates the capabilities of the MQTT protocol in the context of  "Internet of Things" (IoT).

## Prerequisites ##

Install the Arduino MQTT library PubSubClient by Nick O'Leary: https://github.com/knolleary/pubsubclient

You can also install the library from the zip file `pubsubclient.zip` added to the repo. This might not be the latest version. 

## Idea ##

An LED and a potentiometer are connected to an ESP32. They act as actuator (LED) and sensor (poti). The ESP32 and two matching Python scripts are talking to each other and exchange information via the MQTT protocol.


1. Poti: The potentiometer values are published under a particular MQTT topic. A matching Python script subscribes to the that topic and receives the potentiometer data.
1. LED: The ESP32 subscribes to a topic a matching Python script publishes under. The Python script publishes the messages "on" or "off".
When the ESP32 receives "on" or "off" it switches on or off the LED, respectively.

## Software Components ##
The project software comprises of two parts: 
1. one Arduino sketch handling poti and LED,
1. two Jupyter notebooks, one to receive MQTT data from the poti, the other to send MQTT messages to the LED.


You find the ESP32 and Python code under the folder `0600_ESP32/0635_MQTT_Poti/`.

## Recommendations for Circuit and Software ##

1. Do not put the ESP32 on the breadboard. If you mounted it to the breadboard (plugged in into the matrix with holes) you would be able to connect wires only from one side of the EPS32. The other side does not provide a free row of holes.  The ESP32 is too wide for the breadboard.
1. Use the breadboard only to mount the potentiometer as well an LED with a 220 Ohms resistor. LED and poti are independent. 
1. Use the male-female jumper cables to connect the breadboard parts with the male end of the jumper cable directly to the ESP32 pins with the female end of the jumper cables.
1. Use 3.3V and GND
1. Connect the poti slider to pin 34 (numbering on the bottom of the ESP32 board).
1. Connect the LED anode to pin 4.

## IoT ##

Try to get it running!
It is cool. By sharing the topics with your friends you can mutually switch on and off the LED of your friend's circuit and read the other's poti values. This distributed interaction is what we call **INTERNET OF THINGS!**

