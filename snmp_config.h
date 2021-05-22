// RFC1213-MIB OIDs
static char sysDescr[] PROGMEM      = "1.3.6.1.2.1.1.1.0";  // read-only  (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysObjectID (.1.3.6.1.2.1.1.2)
//static char sysObjectID[] PROGMEM   = "1.3.6.1.2.1.1.2.0";  // read-only  (ObjectIdentifier)
// .iso.org.dod.internet.mgmt.mib-2.system.sysUpTime (.1.3.6.1.2.1.1.3)
static char sysUpTime[] PROGMEM     = "1.3.6.1.2.1.1.3.0";  // read-only  (TimeTicks)
// .iso.org.dod.internet.mgmt.mib-2.system.sysContact (.1.3.6.1.2.1.1.4)
static char sysContact[] PROGMEM    = "1.3.6.1.2.1.1.4.0";  // read-write (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysName (.1.3.6.1.2.1.1.5)
static char sysName[] PROGMEM       = "1.3.6.1.2.1.1.5.0";  // read-write (DisplayString)
// .iso.org.dod.internet.mgmt.mib-2.system.sysLocation (.1.3.6.1.2.1.1.6)
static char sysLocation[] PROGMEM   = "1.3.6.1.2.1.1.6.0";  // read-write (DisplayString)

// RFC1213 local values
static char locDescr[] PROGMEM      = "RoomGuard ";        // read-only (static)
static uint32_t locUpTime           = 0;                  // read-only (static)
char locContact[32] PROGMEM  = "Paco Lechner ";     // should be read from SD
char locName[32] PROGMEM     = "Serverroom ";        // should be read from SD
char locLocation[32] PROGMEM = "Austria ";          // should be read from SD

// ROOMGUARD-MIB
// 1.3.6.1.4.<PEN>.1.1 = mibSSID
static char mibSSID[] PROGMEM       = "1.3.6.1.4.1.1600.1.1.1.0"; // read-only (DisplayString)


// Helper-Variables for SNMP.
uint32_t prevMillis = millis();
char oid[SNMP_MAX_OID_LEN];
SNMP_API_STAT_CODES iSNMPStatus;
SNMP_ERR_CODES iSNMPError;
