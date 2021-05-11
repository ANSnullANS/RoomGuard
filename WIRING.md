# Wiring
Below, you'll find instructions on how to connect the components together. Basic experience with Arduino and/or electronics recommended ;)

## Pinout
DHT-Sensor
Sensor-PIN | Arduino Pin
---------- | -----------
\+ | 3V3
out | D5
\- | GND

Display (SSD1306 via I²C)
Display-PIN | Arduino Pin
----------- | -----------
GND | GND
VCC | 3V3
SCL | A5
SDA | A4

SD-Card (3.3V version via SPI)
Module-PIN | Arduino Pin
---------- | -----------
GND | GND
VCC | 3V3
MISO | D12
MOSI | D11
SCK | D13
CS | D10

SIM800L 5V Module (requires stable 5V 2A powersupply!)
Module-PIN | Arduino Pin | PSU-Pin
---------- | ----------- | -------
VCC | | OUT+
GND | GND | OUT-
RX | D0 |
TX | D1 |
