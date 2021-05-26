// Device Total RAM
const int16_t iMemTotal = 32000;

/**************************
* RFC1213-MIB OIDs
**************************/
static char sysDescr[] PROGMEM      = "1.3.6.1.2.1.1.1.0";  // read-only  (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysUpTime (.1.3.6.1.2.1.1.3)
static char sysUpTime[] PROGMEM     = "1.3.6.1.2.1.1.3.0";  // read-only  (TimeTicks)
// .iso.org.dod.internet.mgmt.mib-2.system.sysContact (.1.3.6.1.2.1.1.4)
static char sysContact[] PROGMEM    = "1.3.6.1.2.1.1.4.0";  // read-write (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysName (.1.3.6.1.2.1.1.5)
static char sysName[] PROGMEM       = "1.3.6.1.2.1.1.5.0";  // read-write (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysLocation (.1.3.6.1.2.1.1.6)
static char sysLocation[] PROGMEM   = "1.3.6.1.2.1.1.6.0";  // read-write (DisplayString)

// RFC1213 local values
static char locDescr[] PROGMEM      = "RoomGuard";        // read-only (static)
static uint32_t locUpTime           = 0;                  // read-only (static)

#ifdef SNMP_SDCONFIG
  // values should be overwritten by snmp.cfg on SD-card.
  // Do NOT change!
  char locContact[32];
  char locName[32];
  char locLocation[32];
#else
  // load values from flash instead of RAM if no SD-Card is used.
  // Change here if not using SD-Card!
  char locContact[32] PROGMEM  = "Paco Lechner";     
  char locName[32] PROGMEM     = "Serverroom";        
  char locLocation[32] PROGMEM = "Austria";          
#endif

/**************************
* ROOMGUARD-MIB
**************************/
// WiFi Information
// 1.3.6.1.4.1.57477.1.1.1 = mibSSID
static char mibSSID[] PROGMEM       = "1.3.6.1.4.1.57477.1.1.1.0"; // read-only (DisplayString)
// 1.3.6.1.4.1.57477.1.1.2 = mibStatus
static char mibStatus[] PROGMEM     = "1.3.6.1.4.1.57477.1.1.2.0"; // read-only (DisplayString)
// 1.3.6.1.4.1.57477.1.1.3 = mibSignal
static char mibSignal[] PROGMEM     = "1.3.6.1.4.1.57477.1.1.3.0"; // read-only 

// Sensor(s)
// 1.3.6.1.4.1.57477.1.2.1.1 = mibSensor0Temp
static char mibSensor0Temp[] PROGMEM  = "1.3.6.1.4.1.57477.1.2.1.1.0"; // read-only (Integer)
// 1.3.6.1.4.1.57477.1.2.1.2 = mibSensor0Temp
static char mibSensor0Humid[] PROGMEM  = "1.3.6.1.4.1.57477.1.2.1.2.0"; // read-only (Integer)

// System Information
// 1.3.6.1.4.1.57477.1.100.1 = mibMemTotal
static char mibMemTotal[] PROGMEM = "1.3.6.1.4.1.57477.1.100.1.0"; // read-only (Integer)
// 1.3.6.1.4.1.57477.1.100.2 = mibMemFree
static char mibMemFree[] PROGMEM = "1.3.6.1.4.1.57477.1.100.2.0"; // read-only (Integer)


/**************************
* Helper-Variables for SNMP.
**************************/
uint32_t prevMillis = millis();
char oid[SNMP_MAX_OID_LEN];
SNMP_API_STAT_CODES iSNMPStatus;
SNMP_ERR_CODES iSNMPError;

/**************************
* WiFi-Status Strings
**************************/
char *WiFiStatusStrings[] PROGMEM = {
  "IDLE",
  "NO SSID AVAIL",
  "SCAN COMPLETE",
  "CONNECTED",
  "CONNECT FAILED",
  "CONNECTION LOST",
  "DISCONNECTED"
};

char WiFiStatusNoModule[] PROGMEM = "NO MODULE";
