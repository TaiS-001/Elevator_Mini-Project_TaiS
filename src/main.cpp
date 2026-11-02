#include <Arduino.h>

int b1, b1Last, b2, b2Last, b3, b3Last;
int targetFloor;

void setup() {
  Serial.begin(115200);
  Serial.println("System Ready!");

  pinMode(26, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
}

void loop() {
  b1 = !digitalRead(26);
  b2 = !digitalRead(25);
  b3 = !digitalRead(23);

  if (b1 == 1)
    targetFloor = 1;
  else if (b2 == 1)
    targetFloor = 2;
  else if (b3 == 1)
    targetFloor = 3;
  

  Serial.print("B1: ");
  Serial.print(b1);
  
  Serial.print(" | B2: ");
  Serial.print(b2);
  
  Serial.print(" | B3: ");
  Serial.print(b3);
  
  Serial.print(" | target floor: ");
  Serial.print(targetFloor);

  Serial.println();

  delay(100);
}