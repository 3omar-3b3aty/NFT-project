#include <EEPROM.h>
#include "GravityTDS.h"
#define TdsSensorPin A1
GravityTDS gravityTds;
float temperature = 25, tdsValue = 0;
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
void setup() {
  Serial.begin(9600);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  
  gravityTds.setAdcRange(1024); 
  gravityTds.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("--- Sensors Reading System Started ---");
}
void loop() {
  gravityTds.setTemperature(temperature); 
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.print(" ppm | ");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}