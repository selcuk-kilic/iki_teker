#include "ahrs.h"

AHRS ahrs;

void setup() {
  Serial.begin(9600);
  
  ahrs.setup();
}


void loop() {
  float roll=-1, pitch=-1, heading=-1;
  
  if(ahrs.loop(&pitch, &roll, &heading)) {
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
  }
}
