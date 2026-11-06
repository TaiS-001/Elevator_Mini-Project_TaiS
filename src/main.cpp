#include <Arduino.h>

#define B1 27
#define B2 25
#define B3 26

const int TRIG = 18;
const int ECHO = 19;

//const int IN1 = 14;
//const int IN2 = 12;
//const int IN3 = 13;
//const int IN4 = 23;

int b1, b2, b3;
int targetFloor = 1;

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);

  if (duration == 0)
    return -1;

  return duration * 0.343 / 2;
}

void setup() {
  Serial.begin(115200);

  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  //pinMode(IN1, OUTPUT);
  //pinMode(IN2, OUTPUT);
  //pinMode(IN3, OUTPUT);
  //pinMode(IN4, OUTPUT);
}

void loop() {
  b1 = !digitalRead(B1);
  b2 = !digitalRead(B2);
  b3 = !digitalRead(B3);

  if (b1 == 1)
    targetFloor = 1;
  else if (b2 == 1)
    targetFloor = 2;
  else if (b3 == 1)
    targetFloor = 3;
  
  long distance = readDistance(TRIG, ECHO);

  Serial.print("distance: ");
  Serial.print(distance);

  Serial.print(" | B1: ");
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