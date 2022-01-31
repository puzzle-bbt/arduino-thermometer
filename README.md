# arduino-thermometer
A Puzzle-bbt project to measure temperature and humidity

## Hilfsmittel

### Hardware

* [WeMos D1 mini ESP8266 NodeMcu Lua Board](https://www.bastelgarage.ch/esp8266-esp32/esp-boards/wemos-d1-mini-esp8266-nodemcu-lua-board)
* [WeMos D1 Mini LIPO Batterie Shield V1.2.0](https://www.bastelgarage.ch/esp8266-esp32/esp-shields/wemos-d1-mini-lipo-batterie-shield-v1-2-0?limit=100)
* [Li-Ion Akku 3000mA 18650 mit Schutzelektronik und Stecker](https://www.bastelgarage.ch/li-ion-akku-3000ma-18650-mit-schutzelektronik-und-stecker)
* [WeMos D1 Mini DHT11 Shield](https://www.bastelgarage.ch/esp8266-esp32/esp-shields/wemos-d1-mini-dht11-shield?limit=100)
* [Wemos OLED Shield V2.0.0 Blau I2c 64×48 0.66’’](https://www.bastelgarage.ch/esp8266-esp32/esp-shields/wemos-oled-shield-v2-0-0-blau-i2c-64-48-0-66?limit=100)

Das System besteht aus vier Boards (von oben nach unten):

- Kleines Display mit zwei Tasten
- Der Microcontroller mit einer onboard LED und der Reset-Taste
- Der Batterie Shield, zum Anschliessen der 3V Batterie
- Der Temperatur- und Feuchtigkeits-Sensor (zu unterst, damit die Temperaturmessung nicht von der Abwärme des Systems verfälscht wird)


### Vorbereitung

#### Installation der Arduino IDE
Die Installation könnt ihr einfach mit apt durchführen:

    sudo apt install arduino

Anschliessend müssen die Einstellungen des Programms angepasst werden: 
1. Unter **File / Preferences**:
    * *Sketchbook location* auf das Rootverzeichnis des Arduino GIT Repo setzen
    * *Additional Boards manager URLs* setzen:
  `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
1. Bord installieren: **Tools / Board / Boards Manager**
  Nach dem Board `esp8266` suchen und installieren.
1. Aktuelles Board setzen: **Tools / Board** setzen: `LOLIN(WEMOS) D1 R2 & mini`

Folgende Libraries müssen noch über den Library manager installiert werden: (**Sketch/Import Library/Manage Libraries...**)
* DHT Sensor Library (installiert auch Adafruit Unified Sensor)
