int sensorReading() {
  soil_moist = 1024 - analogRead(A0);
  // print out the value you read:
  Serial.println( (String)"Soil Moist: " + soil_moist );
  delay(500);        // delay in between reads for stability
  return soil_moist;
}


//pump control
bool pumpStatus_current = false ;
bool pumpStatus_previous = false;
void pump_on() {
  digitalWrite(relayPin, HIGH);

  data = weblink + "ON";

  Serial.println(data);
  pumpStatus_current = true;
  sendToServerOnce();
}


void pump_off() {
  digitalWrite(relayPin, LOW);
  data = weblink + "OFF";
  pumpStatus_current = false;
  Serial.println(data);
  sendToServerOnce();
}
