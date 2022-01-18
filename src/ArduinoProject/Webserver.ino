#define CONTENT_TYPE "text/html;charset=utf-8"

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // Type of sensor in use



String HTML_START = "<h1>Hello from esp8266</h1>";

void initWebserver() {
  server.on("/", handleRoot); // what happens in the root
  server.on("/on",led_on); // turn led on from webpage /on
  server.on("/off", led_off); // turn led off from webpage /off
  server.begin();
}

void handleRoot() {
  String ledIs = "off";
  server.send(200, CONTENT_TYPE, 
    HTML_START
    + "<p>LED is '"
    + getLedState()
    + "'.<br><a href='/on'>Turn LED on</a> | <a href='/off'>Turn LED off</a></p>"
    + "<br>"
    + "<p>Temperature is: '"
    + getTemperature()
    + "'</p>"
     + "<br>"
    + "<p>Humidity is: '"
    + getHumidity()
    + "'</p>"
     + "<br>"
    + "<p>Heat Index is: '"
    + getHeatIndex()
    + "'</p>"
  );
}

void led_on(){
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, CONTENT_TYPE, 
    HTML_START 
      + "<p>LED is '"
    + getLedState()
    + "'.<br><a href='/on'>Turn LED on</a> | <a href='/off'>Turn LED off</a></p>"
    + "<br>"
    + "<p>Temperature is: '"
    + getTemperature()
    + "'</p>"
     + "<br>"
    + "<p>Humidity is: '"
    + getHumidity()
    + "'</p>"
     + "<br>"
    + "<p>Heat Index is: '"
    + getHeatIndex()
    + "'</p>"
  );
}

void led_off(){
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, CONTENT_TYPE, 
    HTML_START 
     + "<p>LED is '"
    + getLedState()
    + "'.<br><a href='/on'>Turn LED on</a> | <a href='/off'>Turn LED off</a></p>"
    + "<br>"
    + "<p>Temperature is: '"
    + getTemperature()
    + "'</p>"
     + "<br>"
    + "<p>Humidity is: '"
    + getHumidity()
    + "'</p>"
     + "<br>"
    + "<p>Heat Index is: '"
    + getHeatIndex()
    + "'</p>"
  );
  
}

/*
 * Get the state of the onboard LED line on or off
 */
String getLedState() {
  int led_state = digitalRead(LED_BUILTIN);
  if (led_state == LOW) {
    return "on";
  }
  return "off";
}

float getHumidity() {
   float h = dht.readHumidity();
   if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return h;
  }
}

float getTemperature() {
    float t = dht.readTemperature();
    return t;
}

float getHeatIndex() {
     float h = dht.readHumidity();
     float t = dht.readTemperature();
    float hic = dht.computeHeatIndex(t, h, false);
    return hic;

}
