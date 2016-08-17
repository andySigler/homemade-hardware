#include <IRremote.h>

IRrecv irrecv(11);

decode_results results;

void setup(){
  Serial.begin(9600);
  
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {

    int total_bits = results.rawlen;
    Serial.print("Total Bits: ");
    Serial.println(total_bits);
  
    Serial.print("{");
    for (int i = 1; i < total_bits; i++) {
      Serial.print(results.rawbuf[i]*USECPERTICK, DEC);
      if (i < total_bits - 1){
        Serial.print(",");
      }
    }
    Serial.println("}");
    
    irrecv.resume();
  }
}
