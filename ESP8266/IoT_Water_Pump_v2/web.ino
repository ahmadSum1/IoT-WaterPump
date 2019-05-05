
void webSetup() {
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("TECHCOM-TURBO", "techcomadmin@71"); // wifi-pass

}

//void postOnceEveryChange() {
//  if (updated == false) {
//    String data = weblink + pump_status;
//    serverPost(data);//post into server
//  }
//}



void serverPost(String link) {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, link)) {  // HTTP
      // start connection and send HTTP header
      int httpCode = http.GET();
      Serial.print("posted:");
      Serial.print(link);
      updated == true;
      http.end();
    }
    else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
}



void sendToServerOnce() {
  if (pumpStatus_previous != pumpStatus_current) {
    pumpStatus_previous = true;
    if (pumpStatus_current) {
      pumpStatus_previous = true;
    }
    else if (!pumpStatus_current) {
      pumpStatus_previous = false;
    }
    Serial.println("Sending to server done Once");
    serverPost(data);
  }
}
