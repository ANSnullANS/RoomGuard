# SNMP Agent Features
A simple SNMP agent is implemented with a ported version of "Agentuino" Library by Eric C. Gionet <lavco_eg@hotmail.com> which was also extended by Petr Domorazek.
The portation was required so that the library is capable of running on WiFiNINA based devices (tested with Arduino Nano 33 IoT) instead of using an EthernetShield.

The ported version is available on Github <https://github.com/ANSnullANS/Agentuino>.

## Configuration

RoomGuard is listening on port 161/upd (default SNMP port).

The values for Name, Contact and Location (RFC1213) are limited to 32 characters by default to safe memory. Increase their array-size in "snmp_config.h" if needed.

### Without SD-Card
In "config.h":
- make sure that `#define SNMP_ENABLED true` is *NOT* commented out!
- make sure that `#define SNMP_SDCONFIG true` is commented out!

In "snmp_config.h":
- Update value of `char locContact[32] PROGMEM` to your local Contact for this RoomGuard Device.
- Update value of `char locName[32] PROGMEM` to the Name of this RoomGuard Device (use whatevery feels right ;) ).
- Update value of `char locLocation[32] PROGMEM` to the physical location of this RoomGuard Device.

### Load config from SD-Card
This requires that all settings are loaded from SD-Card (rg.cfg)!

In "config.h":
- make sure that `#define SNMP_ENABLED true` is *NOT* commented out!
- make sure that `#define SNMP_SDCONFIG true` is *NOT* commented out!

On SD-Card:
- create new file named "snmp.cfg"
- Insert values into "snmp.cfg":
-- Name of this RoomGuard Device (e.g. roomguard01)
-- Location (e.g. Server-Room)
-- Contact (e.g. Paco Lechner)

# Implemented Parameters
All parameters are implemented for SNMPGET only!

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