#include <EEPROM.h>
#include "GravityTDS.h"
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define DHTPIN 12              
#define DHTTYPE DHT22
#define ONE_WIRE_BUS 13       
#define TdsSensorPin A1       
const int trigPin = 10;       
const int echoPin = 11;     
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature waterSensors(&oneWire);
GravityTDS gravityTds;
void setup() {
  Serial.begin(9600);
  dht.begin();
  waterSensors.begin();
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("--- Full Monitoring System Initialized ---");
}
void loop() {
  float airTemp = dht.readTemperature();
  float humidity = dht.readHumidity();
  waterSensors.requestTemperatures();
  float waterTemp = waterSensors.getTempCByIndex(0);
  if (waterTemp != -127.00) {
    gravityTds.setTemperature(waterTemp); 
  } else {
    gravityTds.setTemperature(25);       
  }
  gravityTds.update();
  float tdsValue = gravityTds.getTdsValue();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Air: "); 
  Serial.print(airTemp, 1); Serial.print("C / "); 
  Serial.print(humidity, 1); Serial.print("% | ");
  Serial.print("Water: "); 
  if (waterTemp == -127.00) Serial.print("ERR | "); 
  else { Serial.print(waterTemp, 1); Serial.print("C | "); }
  Serial.print("TDS: "); 
  Serial.print(tdsValue, 0); Serial.print(" ppm | ");
  Serial.print("Dist: "); 
  Serial.print(distance); Serial.println(" cm");
  delay(2000);
}