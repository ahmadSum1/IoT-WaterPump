/*
	IoT_Water_Pump.ino

	Controlling motor with soil moisture reading.
  Motor will turn ON if the value is less than minimum moist and will turn OFF if the value cross max moist.
  hits a link every time the pump status is changed from "off" to "on" (or "on" to "off") and make a 
  http post in the server. 
  The data is then shown in a basic table here: http://iotpump.ahmadsum1.dx.am/

	The circuit:
  * ESP8266 (NodeMCU as main MCU)
	* Analog soil moisturesensor connected to A0
	* A 5V single channel relay connectedto D1

	Created 4 May 2019
	By Sakib Ahmed

	https://github.com/ahmadSum1/IoT-WaterPump

*/




#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

String weblink = "http://iotpump.ahmadsum1.dx.am/get.php?data=";  //should add ur custom website link



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
