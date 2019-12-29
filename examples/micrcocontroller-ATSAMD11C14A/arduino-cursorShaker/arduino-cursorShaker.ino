#include "Mouse.h"

int shakeDelay = 40;  // milliseconds between movements
int moveRange = 10;   // max number of pixels to shake
int ledDelay = 10;

int ledPin = 5;

// keeping the shaking within a few pixels
// ensures the cursor on screen doesn't
// get out of control
int x = moveRange / 2;
int y = moveRange / 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Mouse.begin();
  x = moveRange / 2;
  y = moveRange / 2;
}

void loop() {
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
