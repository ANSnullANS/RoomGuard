# SNMP Agent Features
A simple SNMP agent is implemented with a ported version of "Agentuino" Library by Eric C. Gionet <lavco_eg@hotmail.com> which was also extended by Petr Domorazek.
The portation was required so that the library is capable of running on WiFiNINA based devices (tested with Arduino Nano 33 IoT) instead of using an EthernetShield.

The ported version is available on Github <https://github.com/ANSnullANS/Agentuino>.

# Implemented Parameters
## MIB
If you're using any SNMP-Collector which is capable of working with MIB files, copy "ROOMGUARD-MIB.txt" to it's MIB-Storage and/or load the MIB manually.

## List of OIDs
If you're implementing some monitoring manually, use the following OIDs in your SNMPGET requests.

### RFC1213-MIB
Parameter | OID | Datatype | Description
--------- | --- | -------- | -----------
sysDescr | 1.3.6.1.2.1.1.1 | DisplayString | Name of the Device
sysUpTime | 1.3.6.1.2.1.1.3 | TimeTicks | Uptime of the Device
sysContact | 1.3.6.1.2.1.1.4 | DisplayString | Contact for this Device
sysName | 1.3.6.1.2.1.1.5 | DisplayString | Name of the Device
sysLocation | 1.3.6.1.2.1.1.6 | DisplayString | Location of the Device

### ROOMGUARD-MIB
Parameter | OID | Datatype | Description
--------- | --- | -------- | -----------
WiFi SSID | 1.3.6.1.4.1.1600.1.1.1 | DisplayString | Configured SSID
WiFi Status | 1.3.6.1.4.1.1600.1.1.2 | DisplayString | Status-String for WiFi Connection
WiFi Signal | 1.3.6.1.4.1.1600.1.1.3 | Integer32 | Signal Strength in dBm
Sensor0 Temperature | 1.3.6.1.4.1.1600.1.2.1.1 | Integer | Temperature from Sensor0 as integer (divide by 10 to get real value)
Sensor0 Humidity | 1.3.6.1.4.1.1600.1.2.1.2 | Integer | Humidity from Sensor0 as integer (divide by 10 to get real value)
Arduino RAM Total | 1.3.6.1.4.1.1600.1.100.1 | Integer | Total RAM of Arduino MCU
Arduino RAM Free | 1.3.6.1.4.1.1600.1.100.2 | Integer | Free RAM of Arduino MCU

# Credits
Original Agentuino Library:
Copyright (C) 2010 Eric C. Gionet
http://code.google.com/p/agentuino/
License: GNU GPL v2

Extended Agentuino Library:
Petr Domorazek
https://github.com/1sw/Agentuino

# DISCLAIMER
The developer(s) of RoomGuard provide everything as-is and without any kind of warranty what-so-ever especialy for reliability of monitoring data!