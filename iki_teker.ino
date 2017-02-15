#include "ahrs.h"

AHRS ahrs;

void getOrientation(float yaw, float pitch, float roll) {
  Serial.print("Orientation: ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.println(roll);  
}

void setup() {
  Serial.begin(9600);
  ahrs.setup(&getOrientation);
}


void loop() {
  delay(10000);
}
