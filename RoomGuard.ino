#include <SPI.h>
#include <WiFiNINA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "secrets.h" 
#include "config.h"

#ifdef SD_ENABLED
  #include <SPI.h>
  #include <SD.h>
  File oSDFile;
  String sSSID = "";
  String sPSK = "";
#endif

// Variables for WiFi Connection.
int iWiFiStatus = WL_IDLE_STATUS;
WiFiServer oServer(80);
IPAddress WIFI_IP;
char cClientData;

// OLED Display.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT Sensor Variables.
DHT_Unified dht(DHTPIN, DHTTYPE);
bool bHasTemp = false;
bool bHasHumid = false;
sensors_event_t pEvent;

// Update Timing Variables for Display and Sensor.
float fRealTemp = 0.0;
float fRealHumid = 0.0;
long lLastUpdate = 0;
long lUpdateInterval = 2000;
long lNow = 0;
long lLastSensorUpdate = 0;
long lSensorInterval = 5000;

// Setup all components and connect to WiFi.
void setup() {
  Serial.begin(9600);
  // Wait for the serial-port to initialize.
  if(!Serial) {
    delay(3000);
  }

  // Start Display.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show Boot-Screen.
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("RoomGuard"));
  display.setTextSize(1);
  display.println(F("starting up..."));
  display.println();

  // Load Settings from SD-Card if SD_ENABLED is defined.
  #ifdef SD_ENABLED
    if (!SD.begin(SD_CS)) {
      display.println(F("SD-Card failed!"));
      display.display();
      while(true) {
        delay(1);
      }
    }
    display.println(F("SD-Card OK"));
    display.display();

    // Read settings from rg.cfg
    oSDFile = SD.open(F("rg.cfg"), FILE_READ);
    sSSID = oSDFile.readStringUntil('\n');
    sPSK = oSDFile.readStringUntil('\n');
    String sTempCorr = oSDFile.readStringUntil('\n');
    String sHumiCorr = oSDFile.readStringUntil('\n');
    String GSM_ALERT_PHONE = oSDFile.readStringUntil('\n');
    String sAlertTemp = oSDFile.readStringUntil('\n');
    String sAlertHumi = oSDFile.readStringUntil('\n');

    // Process/Convert strings from config-file.
    int iSSIDLen = sSSID.length();
    char aSSID[iSSIDLen];
    sSSID.toCharArray(aSSID, iSSIDLen);
    int iPSKLen = sPSK.length();
    char aPSK[iPSKLen];
    sPSK.toCharArray(aPSK, iPSKLen);

    TEMP_CORRECT = sTempCorr.toFloat();
    HUMID_CORRECT = sHumiCorr.toFloat();
    ALERT_TEMP = sAlertTemp.toFloat();
    ALERT_HUMID = sAlertHumi.toFloat();

    display.print(F("SSID: \""));
    display.print(aSSID);
    display.println(F("\""));

    #ifdef DEBUG
      Serial.print(F("Phone: "));
      Serial.println(GSM_ALERT_PHONE);
      Serial.print(F("Temp Corr:"));
      Serial.println(TEMP_CORRECT);
      Serial.print(F("Humi Corr:"));
      Serial.println(HUMID_CORRECT);
      Serial.print(F("Alert Temp:"));
      Serial.println(ALERT_TEMP);
      Serial.print(F("Alert Humid:"));
      Serial.println(ALERT_HUMID);
    #endif
  #else
    // If SD-Card is not enabled, use settings from config.h and secrets.h
    char aSSID[] = SECRET_SSID;
    char aPSK[] = SECRET_PASS;
    display.print(F("SSID: "));
    display.println(SECRET_SSID);
  #endif
  
  display.display();


  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    display.println(F("WiFi Module Error"));
    display.display();
    // don't continue
    while (true);
  }

  #ifdef DEBUG
    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
      display.println(F("FW Upgrade available!"));
      display.display();
    }
  #endif

  display.print(F("Connecting."));
  display.display();

  while (iWiFiStatus != WL_CONNECTED) {
    display.print(".");
    display.display();
    iWiFiStatus = WiFi.begin(aSSID, aPSK);
    delay(5000);
  }
  display.println(F("OK"));
  display.display();
  WIFI_IP = WiFi.localIP();
  oServer.begin();

  blackoutScreen();
  printWiFiStatus();

  dht.begin();
}

// Default Process.
void loop() {
  lNow = millis();

  // Update sensor data after refresh-timeout.
  if (lNow >= lLastSensorUpdate + lSensorInterval || lLastSensorUpdate == 0) {
    refreshSensorValues();
    lLastSensorUpdate = lNow;
  }

  // Update display after refresh-timeout.
  if (lNow >= lLastUpdate + lUpdateInterval || lLastUpdate == 0) {
    display.fillRect(0,0,128,64,SSD1306_BLACK);
    printWiFiStatus();
    printSensorValues();
    display.display();
    lLastUpdate = lNow;
  }

  // Check for HTTP-Clients connecting to Device on Port 80.
  WiFiClient oClient = oServer.available();
  if (oClient) {
    #ifdef DEBUG
      Serial.println("new client");
    #endif
    String sCurrentLine = "";
    bool bCurrentLineIsBlank = true;

    // Show RoomGuard Status-XML.
    while (oClient.connected()) {
      if (oClient.available()) {
        cClientData = oClient.read();
        if (cClientData == '\n' && bCurrentLineIsBlank) {
          // Send HTTP response
          oClient.println(F("HTTP/1.1 200 OK"));
          oClient.println(F("Content-Type: text/xml"));
          oClient.println(F("Connection: close"));  // the connection will be closed after completion of the response
          oClient.println(F("Refresh: 5"));  // refresh the page automatically every 5 sec
          oClient.println();
          oClient.println(F("<?xml version=\"1.0\"?>"));
          oClient.println(F("<RoomGuard>"));
          
          // output the values from DHT sensor
          oClient.print(F("<Temperature>"));
          oClient.print(fRealTemp);
          oClient.println(F("</Temperature>"));

          oClient.print(F("<Humidity>"));
          oClient.print(fRealHumid);
          oClient.print(F("</Humidity>"));
          oClient.println("</RoomGuard>");
          break;
          
        } else if (cClientData == '\n') {
          // you're starting a new line
          sCurrentLine = "";
          bCurrentLineIsBlank = true;
        }
      }
    }
    // Delay, so client can properly fetch the data.
    delay(1);
    
    // close the connection
    oClient.stop();
    
    #ifdef DEBUG
      Serial.println("client disconnected");
    #endif
  }
}

// Wipe Screen
void blackoutScreen() {
  display.fillRect(0,0,128,64,SSD1306_BLACK);
  display.display();
}

// Print WiFi Status on Display.
void printWiFiStatus() {
  display.setTextSize(1);
  display.setCursor(0,0);             // Start at top-left corner
  display.println(SECRET_SSID);
  display.print("IP: ");
  display.println(WIFI_IP);
  display.print("Signal: ");
  display.print(WiFi.RSSI());
  display.println(" dBm");
}

// Refresh Sensor-Values from DHT sensor.
void refreshSensorValues() {
  #ifdef DEBUG
    Serial.println(F("Updating Sensor values"));
  #endif
  
  dht.temperature().getEvent(&pEvent);
  if(isnan(pEvent.temperature)) {
    fRealTemp = 0;
    bHasTemp = false;
  }
  else {
    fRealTemp = float(pEvent.temperature) + TEMP_CORRECT;
    bHasTemp = true;
  }
  dht.humidity().getEvent(&pEvent);
  if(isnan(pEvent.relative_humidity)) {
    fRealHumid = 0;
    bHasHumid = false;
  }
  else {
    fRealHumid = float(pEvent.relative_humidity) + HUMID_CORRECT;
    bHasHumid = true;
  }
}

// Print Sensor Values on Display.
void printSensorValues() {
  display.setTextSize(2);
  display.setCursor(0,34);  

  if(bHasTemp) {
    display.print(fRealTemp);
  }
  else {
    display.print(F("EE"));
  }
  display.println(" *C");
 
  if(bHasHumid) {
    display.print(fRealHumid);
  }
  else {
    display.print(F("EE"));
  }
  display.println(" %");
}
