/*
   Code version: 1.01
   Date: 5 May 2019
   Author: Sakib Ahmed



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

String weblink = "http://http://iotpump.ahmadsum1.dx.am/show.php?data=";  //add ur custom website link



bool updated = false; //flag

///////////// relay pin (active "HIGH" type)
int relayPin = D1;
/////////////
int soil_moist;
int max_moist = 800;
int min_moist = 400;
String pump_status = "";
String prev_pump_status = "";
void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  pump_off(); //to make sure the pump is off initially

  webSetup();
}

void loop() {
  soil_moist = 1024 - analogRead(A0);

  // print out the value you read:
  Serial.print( (String)"Soil Moist: " + soil_moist );
  delay(500);        // delay in between reads for stability

  if (soil_moist < min_moist) {
    pump_on();
  }
  if (soil_moist > max_moist) {
    pump_off();
  }

  postOnceEveryChange();
  Serial.println( "      Pump status: " + pump_status );

}


void pump_on() {
  pump_status = "ON";
  digitalWrite(relayPin, HIGH);
  if (prev_pump_status != pump_status) {
    updated = false;
  }
  prev_pump_status = pump_status;

}
void pump_off() {
  pump_status = "OFF";
  digitalWrite(relayPin, LOW);
  if (prev_pump_status != pump_status) {
    updated = false;
  }
  prev_pump_status = pump_status;
}
