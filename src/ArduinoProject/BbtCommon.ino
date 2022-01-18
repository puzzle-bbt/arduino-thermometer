void initSerial() {
  Serial.begin(9600);
  delay(200); // get the serial interface time to initialize
  Serial.println();
}

/* 
 *  Connect to the WiFi.
 */
void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


/*
 * A simple pause function.
 */
void pause() {
    delay(2000);
}


/* 
 *  Wait for a 'A' on the serial input.
 */
void waitForStart() {
  Serial.print("Start with [A] > ");
  String input;
  while(!hasAPressed()) {
    delay(100);
  }
  Serial.printf("\nRead the start command: %s", input.c_str());
}

boolean hasAPressed() {
  if(Serial.available() > 0) {
    char c = Serial.read();
    
    if (c != '\n') Serial.print(c);
    if (c == 'A') return true;
  }
  return false;
}
