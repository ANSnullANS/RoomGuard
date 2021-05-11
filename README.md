# RoomGuard
Room Temperature Monitor with WiFi (and optional GSM) connectivity. Based on Arduino.

## Features
### Working & Tested
- Monitor Temperature and Humidity
- Show Values on OLED Display
- Fetch Values via Webbrowser (XML Format)
  - Can be integrated in most Monitoring tools (e.g. Zabbix, Icinga)
### In Progress
- SMS-Alert support via SIM800L Module

## How to use
### Programming Arduino Nano 33 IoT
1. Download code or clone repository ;)
2. Install Arduino IDE 1.8.13 (or newer)
3. Inside Arduino IDE, install "Arduino SAMD (32bit ARM Cortex-M0+) Boards" via Board Manager.
4. Use Library Manager to install following dependencies:
   1. WiFiNINA 1.8.7
   2. Adafruit GFX Library 1.10.7
   3. Adafruit SSD1306 2.4.4
   4. Adafruit Unified Sensor (DHT) 1.1.4
   5. DHT sensor library 1.4.2
   6. Adafruit BusIO 1.7.3
   7. SD 1.2.4
5. Open "config.h" and update following settings:
   1. "#define SD_ENABLED true": comment this line out if you don't want to use a SD-Card for settings.
   2. "#define GSM_ENABLED true": comment this line out if you don't want to use a SIM800L module for sending alerts.
   3. TEMP_CORRECT: float value to use as temperature-offset/correction if your sensor is a bit off.
   4. HUMID_CORRECT: float value to use as humidity-offset/correction if your sensor is a bit off.
   5. DHTTYPE: either "DHT11" or "DHT22", depending on the sensor you have. I recommend DHT22.
6. Make a copy of secrets.h.sample named "secrets.h".
7. Optional (if not using SD-Card): open "secrets.h" and insert your WiFi Data:
   1. SECRET_SSID: Your SSID
   2. SECRET_PASS: Your Password/PSK
8. Optional (if using SIM800L module, but no SD-Card): open "config.h" and update GSM-Settings:
   1. GSM_ALERT_PHONE: The phone-number you want to send alerts to. (Format: +ZZnnnnnnnn where ZZ is the country-code, and 'n' are digits of the actual number)
   2. ALERT_TEMP: Temperature where to send SMS-Alert.
   3. ALERT_HUMID: Humidity where to send SMS-Alert.
9. Build & Upload Code to your Arduino Nano 33 IOT via IDE.

### SD-Card config-file
1. Copy "rg.cfg.sample" to your FAT32-formated SD-Card as "rg.cfg".
2. Open "rg.cfg" and update the settings to your liking (parameters are position-based, so order is important):
   1. SSID (String)
   2. WiFi-Password/PSK (String)
   3. Temperature Correction (float value)
   4. Humidity Correction (float value)
   5. Alert Phone Number (String)
   6. Alert Temperature (float value)
   7. Alert Humidity (float value)
3. Remove all comments (starting with '#') from rg.cfg. Those are just for explanation!
4. Save rg.cfg on SD-Card.

### Wiring
see WIRING.md (https://github.com/ANSnullANS/RoomGuard/blob/main/WIRING.md)
