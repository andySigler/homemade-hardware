/*

This example demonstrates how the ESP32 can be used as a BLE peripheral (server)

This demo will advertise as a BLE device, and will update it's name when a button is pressed.

It will also turn on/off an LED when the button is pressed.

To test, upload this demo to an ESP32, and connect a button and LED to pins defined below.

Then, using an app like Nordic's nRF Connect, scan for BLE devices and see the ESP32.

When you press the button, the advertised ESP32 name should change within the app.

*/

#include "SimpleBLE.h"

const int button_pin = 25;
const int led_pin = 23;

int prev_button_value = -1;

String adv_name = "ESP32-Demo-";
SimpleBLE ble;

void setup() {
    Serial.begin(115200);
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(led_pin, OUTPUT);
    Serial.println("\n\nStarting Demo");
}

void loop() {
    int button_value = digitalRead(button_pin);
    digitalWrite(led_pin, button_value);
    if(button_value != prev_button_value){
      Serial.println("New value is: " + String(button_value));
      ble.begin(adv_name + String(button_value));
    }
    prev_button_value = button_value;
}
