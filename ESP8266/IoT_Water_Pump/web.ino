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
  WiFiMulti.addAP("pump", "pumppump"); // wifi-pass

}

void postOnceEveryChange() {
  if (updated == false) {
    String data = "http://shaifur.com/api/send.php?data=" + pump_status;
    serverPost(data);
  }
}



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
