///////////// relay pin (active "HIGH" type)
int relayPin = D1;
/////////////

int soil_moist;
int max_moist = 600;
int min_moist = 100;
String pump_status = "";

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);

  pump_off(); //to make sure the pump is off initially
}

void loop() {
  soil_moist = 1023 - analogRead(A0);

  // print out the value you read:
  Serial.print( (String)"Soil Moist: " + soil_moist );
  delay(1);        // delay in between reads for stability

  if (soil_moist < min_moist) {
    pump_on();
  }
  if (soil_moist > max_moist) {
    pump_off();
  }
  Serial.println( "      Pump status: " + pump_status );

}


void pump_on() {
  pump_status = "ON";
  digitalWrite(relayPin, HIGH);
}
void pump_off() {
  pump_status = "OFF";
  digitalWrite(relayPin, LOW);
}
