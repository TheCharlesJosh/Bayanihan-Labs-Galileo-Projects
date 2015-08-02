#include <Servo.h>
#include <Wire.h>

/*
 * 
 */

const int sensorPin1 = A0;
const int sensorPin2 = A1;
const int ledPin1 = 10;
const int ledPin2 = 11;
const int ledPin3 = 12;
const int directionPin = 4;
const int speedPin = 5;
int sensor1 = 0;
int sensor2 = 0;
int prevSensor1 = 0;
int prevSensor2 = 0;
int maxSensorValue1 = 0;
int minSensorValue1 = 1023;
int maxSensorValue2 = 0;
int minSensorValue2 = 1023;
int threshold1 = 0;
int threshold2 = 0;
int count = 0;
int swingPosition = 0;
boolean asserted1 = false;
boolean asserted2 = false;
boolean swingReversed = false;

long swingPrevious = 0;
long swingCurrent = 0;
long swingStagger = 20;

Servo electricFan; 

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(13, OUTPUT);

  electricFan.attach(3);
  electricFan.write(90);

  digitalWrite(4, LOW);
  
  Serial.begin(9600);
  calibration(5000);

  swingPrevious = millis();
}

void loop() {
  sensor1 = analogRead(sensorPin1);
  sensor2 = analogRead(sensorPin2);
  
  Serial.print(threshold1);
  Serial.print(": ");
  Serial.print(sensor1);
  Serial.print(", ");
  Serial.print(threshold2);
  Serial.print(": ");
  Serial.print(sensor2);
  Serial.print(". ");
  Serial.println(count);
  
  if (sensor1 < threshold1) {
    if (sensor1 < threshold1 && prevSensor1 > threshold1) { 
      
      asserted1 ^= 1;
      
      if (asserted2) {
        count++;
        asserted1 = false;
        asserted2 = false;
      }
      
    }
  }
  
  if (sensor2 < threshold2) {
    if (sensor2 < threshold2 && prevSensor2 > threshold2) {
      
      asserted2 ^= 1;
      
      if (asserted1) {
        count--;
        asserted1 = false;
        asserted2 = false;
      }
      
    }
  }
  
  if (count <= 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);

    electricFanSwing(false);
    analogWrite(speedPin, 0);
    
    count = 0;
  } else if (count == 1){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);

    electricFanSwing(false);
    analogWrite(speedPin, 85);
  } else if (count == 2){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);

    electricFanSwing(true);
    analogWrite(speedPin, 85);
  } else if (count == 3){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);

    electricFanSwing(true);
    analogWrite(speedPin, 170);
  } else if (count >= 3){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    
    electricFanSwing(true);
    analogWrite(speedPin, 255);
  }
    
  prevSensor1 = sensor1;
  prevSensor2 = sensor2;
}

void calibration (int millisecondDuration) {
  digitalWrite(13, HIGH);
  for (int i = millis(); i < millisecondDuration; i = millis()){
    sensor1 = analogRead(sensorPin1);
    Serial.print(sensor1);
    Serial.print(", ");
    if (sensor1 < minSensorValue1){
      minSensorValue1 = sensor1;
    }
    if (sensor1 > maxSensorValue1){
      maxSensorValue1 = sensor1;
    }
    sensor2 = analogRead(sensorPin2);
    Serial.println(sensor2);
    if (sensor2 < minSensorValue2){
      minSensorValue2 = sensor2;
    }
    if (sensor2 > maxSensorValue2){
      maxSensorValue2 = sensor2;
    }
  }
  threshold1 = (maxSensorValue1 + minSensorValue1)/2;
  threshold2 = (maxSensorValue2 + minSensorValue2)/2;
  Serial.println(threshold1);
  Serial.println(threshold2);
  digitalWrite(13, LOW);
}

void electricFanSwing (boolean enabled) {
  swingCurrent = millis();
  if (swingCurrent - swingPrevious >= swingStagger) {
    if (enabled) {
      electricFan.write(swingPosition);
      if (swingPosition == 180) {
        swingReversed = true;
      } else if (swingPosition == 0) {
        swingReversed = false;
      }
      swingPosition += swingReversed ? -1 : 1;
    }
    swingPrevious = swingCurrent;
  }
}

