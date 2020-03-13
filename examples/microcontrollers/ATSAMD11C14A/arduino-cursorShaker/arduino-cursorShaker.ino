/*

This demo uses that ATSAMD11C14A to control the mouse of the connected computer

The ATSAMD11C14A must first have the Arduino bootload flashed:
   -> http://homemadehardware.com/guides/recommended-parts/#atsamd11c14

Then, upload this code over a USB cable. Because this microcontroller does not
come with a USB connector, you will need to do one of the following:

  a) attach a USB connector to the microcontroller
  b) cut a USB cable, solder headers to the wires, and connect the wires to your microcontroller

When the button is pressed, the LED will flash, and the cursor of any connected computer
will randomly jump around a few pixels (not too much, that would be annoying...)

*/

#include "Mouse.h"

int buttonPin = 15;
int ledPin = 4;

int shakeDelay = 40;  // milliseconds between movements
int moveRange = 10;   // max number of pixels to shake
int ledDelay = 10;

// keeping the shaking within a few pixels
// ensures the cursor on screen doesn't
// get out of control
int x = moveRange / 2;
int y = moveRange / 2;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Mouse.begin();
  x = moveRange / 2;
  y = moveRange / 2;
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    int newX = random(0, moveRange);
    int newY = random(0, moveRange);
    // Mouse.move() uses relative distances
    Mouse.move(newX - x, newY - y, 0);
    x = newX;
    y = newY;
    digitalWrite(ledPin, LOW);
    delay(ledDelay);
    digitalWrite(ledPin, HIGH);
    delay(max(shakeDelay - ledDelay, 0));
  }
}
