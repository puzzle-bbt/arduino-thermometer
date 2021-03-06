#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // Type of sensor in use

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


// Button
// constants won't change. They're used here to set pin numbers:
const int buttonA = 14;     // GPIO14 => WeMos D1 mini: Pin D5
const int buttonB = 12;     // GPIO12 => WeMos D1 mini: Pin D6

// variables will change:
int buttonStateA = 0;
int buttonStateB = 0;


// RESTClient
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WIFI_SSID "puzzleguest"
#define WIFI_PASSWORD "Tarwinn7"


boolean onMenuPage = false;
boolean onChangingPage = false;


void setup() { 
  initSerial();
  // Initialize DHT11
  dht.begin();
  delay(2000);

  // by default, we'll generate the high voltage from the 3.3v line internally! 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);


  //Button
  // initialize the buttons as inputs
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);


}

void loop() {
  menuButtonPressed();
  String urlParams;
  
  if(onMenuPage) {
    if (onChangingPage) {
      showChangingPage();
    } else {
     showMenu();
    }
  } 
  else {
     urlParams = getMeasurment();
  }


  sendRestCall(urlParams);
}

void sendRestCall(String urlParams) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      HTTPClient http;  //Declare an object of class HTTPClient
      String url = "http://10.13.252.3:8080/sendDatas/" + urlParams;
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET();
      Serial.println(httpCode);

      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);             //Print the response payload
      }

      http.end();   //Close connection
    }

    delay(5000);
}

String getMeasurment() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return "Failed to read";
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Luftfeuchtigkeit: "));
  Serial.print(h);

  Serial.print(F("%;  Temperatur: "));
  Serial.print(t);
  Serial.print(F("??C "));

  Serial.print(F(";  Hitzeindex: "));
  Serial.print(hic);
  Serial.print(F("??C "));
  Serial.println();


  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  
  display.print("LFK: ");
  display.print(h);
  display.println();

  display.print("TMP: ");
  display.print(t);
  display.println();

  display.print("HI: ");
  display.print(hic);
  display.println();
  display.println();
  
  display.println("For options: Click A");
  display.display();

  String url = "" + String(t,2) + "/" + String(h,2) + "/" + String(hic,2); // Build string with 2 decimal places
  return url;

 
  delay(100);
}

boolean menuButtonPressed() {
  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
   
  if (buttonStateA == LOW) {  
    onMenuPage = true;
    return true;
  } else if (buttonStateB == LOW && !onChangingPage) {
      onMenuPage = false;
      return false;
  }

  delay(100);
  pause();
}

void showMenu() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Press A to change webserver state");
  display.println("Press B to go back");
  display.println();
  display.display();


  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
   
  if (buttonStateA == LOW) {
      onChangingPage = true;
   }
   else if (buttonStateB == LOW) {
    onMenuPage = false;
    onChangingPage = false;
  }

  delay(100);
  pause();
}

void showChangingPage() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Press A to go back");
  display.println("Press B to stop WS");
  display.display();

  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
 
  if (buttonStateA == LOW) {
      onChangingPage = false;
      onMenuPage = true;
   }
   else if (buttonStateB == LOW) {
     changeWebserver("stop");
     onChangingPage = false;
     onMenuPage = false;
  }


  delay(100);
  pause();
}

void changeWebserver(String changing) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      HTTPClient http;  //Declare an object of class HTTPClient
      String url = "http://10.13.252.3:8080/changeWebserver/" + changing;
      Serial.println(url);
      http.begin(url);
      int httpCode = http.GET();
      Serial.println(httpCode);

      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);             //Print the response payload
      }

      http.end();   //Close connection
    }

    delay(5000);

}
