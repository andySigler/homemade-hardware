#include <IRremote.h>

IRsend irsend;

int pulse_khz = 38;

unsigned int samsung[] = {4500, 4350, 600, 1600, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 1600, 550, 1650, 550, 550, 550, 550, 550, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 550, 1650, 550};
unsigned int epson[] = {8800, 4400, 650, 1550, 650, 1550, 650, 500, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1600, 600, 1600, 650, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 650, 1550, 650, 500, 600, 500, 600, 500, 650, 500, 600, 500, 600, 1600, 600, 500, 650, 500, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 600, 500, 650, 1550, 600, 1650, 550, 550, 600};

unsigned int samsung_bit_length = sizeof(samsung) / sizeof(samsung[0]);
unsigned int epson_bit_length = sizeof(epson) / sizeof(epson[0]);

void setup(){
}

void loop() {

  // the projectors
  irsend.sendRaw(epson, epson_bit_length, pulse_khz);
  
  delay(20);

  // the TV's
  irsend.sendRaw(samsung, samsung_bit_length, pulse_khz);
  
  delay(500);
}
