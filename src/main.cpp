#include <Arduino.h>

#define B1 27
#define B2 25
#define B3 26

const int TRIG = 18;
const int ECHO = 19;

const int IN1 = 14;
const int IN2 = 12;
const int IN3 = 13;
const int IN4 = 23;

const int f1Dist = 135;
const int f2Dist = 225;
const int f3Dist = 335; 

const int error = 5;

int val;

int b1, b2, b3;
int targetFloor = 1;

int targetDist;
long distance;
long diff;

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

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  if(val == 0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
      
    delay(2);
      
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
      
    delay(2);
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
      
    delay(2);
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
    delay(2);
  }
  else if(val == 1)
  {
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);

    delay(2);
    
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);

    delay(2);

    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);

    delay(2);

    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH);

    delay(2);
  }
  else if (val == -1)
  {
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
  }
  
  b1 = !digitalRead(B1);
  b2 = !digitalRead(B2);
  b3 = !digitalRead(B3);

  if (b1 == 1)
    targetFloor = 1;
  else if (b2 == 1)
    targetFloor = 2;
  else if (b3 == 1)
    targetFloor = 3;
  
  distance = readDistance(TRIG, ECHO);

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
  
  Serial.print(" | direction: ");
  if (val == 0)
    Serial.print("up");
  else if (val == 1)
    Serial.print("down");
  else if (val == -1)
    Serial.print("stop");

  targetDist = f1Dist;
  if (targetFloor == 2) 
    targetDist = f2Dist;
  else if (targetFloor == 3) 
    targetDist = f3Dist;

  if (distance > 0) {
    diff = distance - targetDist;
    if (abs(diff) <= error)
      val = -1;
    else if (diff < 0) 
      val = 0; 
    else
      val = 1;
    
  }
  else
    val = -1;

  Serial.println();
  delay(50);
}