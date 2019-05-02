///////////// motor pins
int motorPinA=2;
int motorPinB=3;
/////////////

int soil_moist;
int max_moist=600;
int min_moist=100;
String pump_status="";

void setup() {
  Serial.begin(9600);

  pinMode(motorPinA,OUTPUT);
  pinMode(motorPinB,OUTPUT);

  pump_off(); //to make sure the pump is off initially
}

void loop() {
  soil_moist = 1023-analogRead(A0);
  
  // print out the value you read:
  Serial.print( (String)"Soil Moist: "+soil_moist );
  delay(1);        // delay in between reads for stability

  if(soil_moist<min_moist){
    pump_on();
   }
  if(soil_moist>max_moist){
    pump_off();
   }
  Serial.println( "      Pump status: "+pump_status );
   
}


void pump_on(){
    pump_status="ON";
    digitalWrite(motorPinA, HIGH);
    digitalWrite(motorPinB, LOW);  
  }
void pump_off(){
    pump_status="OFF";
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, LOW);
  }
