#define DEBUG       true

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define DHTPIN 5
#define DHTTYPE    DHT22

float TEMP_CORRECT = 0.0;
float HUMID_CORRECT = 0.0;

// Uncomment GSM_ENABLED to make use of SMS-Functions
#define GSM_ENABLED       true
String  GSM_ALERT_PHONE = "+430000000";
float   ALERT_TEMP =      30.0;
float   ALERT_HUMID =     40.0;

//#define SD_ENABLED    true
#define SD_CS       10            // Use D10 when using WiFi - SD-Card can't be used together with W5500 module!

// Display-Options
#define WIFI_SIGNAL_BAR   true

// SNMP Agent Settings
#define SNMP_ENABLED      true
// Load SNMP config from SD-Card.
//#define SNMP_SDCONFIG     true

// Network Settings
//#define WIFI_ENABLED      true
#define ETH_ENABLED       true
