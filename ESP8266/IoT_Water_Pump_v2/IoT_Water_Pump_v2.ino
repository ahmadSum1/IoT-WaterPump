/*
   Code version: 2.0
   Date: 5 May 2019
   Original version: Sakib Ahmed
   V2: Shaifur Rahman



   ###########Application###########

   Controlling motor with soil moisture reading.
   Motor will turn ON if the value is less than minimum moist and will turn OFF if the value cross max moist.

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

String weblink = "http://shaifur.com/api/send.php?data=";

String data;

boolean updated = false; //flag

// relay pin (active "HIGH" type)
int relayPin = D1;
int soil_moist;
int max_moist = 800;  // Max Moist
int min_moist = 400;  // Minimum Moist
void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  pump_off(); //to make sure the pump is off initially
  webSetup();
}

void loop() {
  if (sensorReading() > max_moist) {
    pump_off();
  }
  else if(sensorReading() < min_moist){
    pump_on();
    }
}
