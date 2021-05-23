#ifdef SNMP_ENABLED
#include <Streaming.h>

char aResponse[64];
String sSetting;

#ifdef SD_ENABLED
  void readSNMPDatafromSD() {
    oSDFile = SD.open(F("snmp.cfg"), FILE_READ);
    sSetting = oSDFile.readStringUntil('\n'); // Read sysName
    sSetting.toCharArray(locName, sSetting.length());
    sSetting = oSDFile.readStringUntil('\n'); // Read sysLocation
    sSetting.toCharArray(locLocation, sSetting.length());
    sSetting = oSDFile.readStringUntil('\n'); // Read sysContact
    sSetting.toCharArray(locContact, sSetting.length());
    oSDFile.close();

    #ifdef DEBUG
      Serial.print(F("sysName: "));
      Serial.println(locName);
      Serial.print(F("sysLocation: "));
      Serial.println(locLocation);
      Serial.print(F("sysContact: "));
      Serial.println(locContact);
    #endif
  }
#endif

void pduReceived()
{
  SNMP_PDU oPDU;
  iSNMPStatus = Agentuino.requestPdu(&oPDU);
  
  if ((oPDU.type == SNMP_PDU_GET || oPDU.type == SNMP_PDU_GET_NEXT || oPDU.type == SNMP_PDU_SET)
    && oPDU.error == SNMP_ERR_NO_ERROR && iSNMPStatus == SNMP_API_STAT_SUCCESS ) {
    //
    oPDU.OID.toString(oid);

    #ifdef DEBUG
      Serial.print(F("SNMP Req. "));
      Serial.println(oid);
    #endif
    
    if ( strcmp_P(oid, sysDescr ) == 0 ) {
      // handle sysDescr (set/get) requests
      if ( oPDU.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read-only
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = SNMP_ERR_READ_ONLY;
      } else {
        // response packet from get-request - locDescr
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, locDescr);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
      //
    } else if (strcmp_P(oid, mibSSID) == 0) { // SSID Requested
      if ( oPDU.type == SNMP_PDU_GET ) {
        // Convert SSID to OCTETS and send back.
        sSSID.toCharArray(aResponse, 64);
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, aResponse);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else if (strcmp_P(oid, mibSignal) == 0) { // WiFi Signal Strength requested
       if ( oPDU.type == SNMP_PDU_GET ) {
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_INT, int16_t(iWiFiSignal));
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else if (strcmp_P(oid, mibStatus) == 0) { // WiFiStatus Requested
        if ( oPDU.type == SNMP_PDU_GET ) {
          if (iWiFiStatus == 255) {
            iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, WiFiStatusNoModule);
          }
          else {
            iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, WiFiStatusStrings[iWiFiStatus]);
          }
          oPDU.type = SNMP_PDU_RESPONSE;
          oPDU.error = iSNMPError;
        }
    } else if ( strcmp_P(oid, sysUpTime ) == 0 ) {
      // handle sysName (set/get) requests
      if ( oPDU.type == SNMP_PDU_GET ) {
        // response packet from get-request - locUpTime
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_TIME_TICKS, locUpTime);       
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
      //
    } else if (strcmp_P(oid, mibMemTotal) == 0) {
      if (oPDU.type == SNMP_PDU_GET) {
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_INT, iMemTotal);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else if (strcmp_P(oid, mibMemFree) == 0) {
      if (oPDU.type == SNMP_PDU_GET) {
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_INT, int16_t(iFreeMemory));
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else if ( strcmp_P(oid, sysName ) == 0 ) {
      // handle sysName (set/get) requests
      if ( oPDU.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = oPDU.VALUE.decode(locName, strlen(locName)); 
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      } else {
        // response packet from get-request - locName
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, locName);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
      //
    } else if ( strcmp_P(oid, sysContact ) == 0 ) {
      // handle sysContact (set/get) requests
      if ( oPDU.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = oPDU.VALUE.decode(locContact, strlen(locContact)); 
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      } else {
        // response packet from get-request - locContact
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, locContact);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
      //
    } else if ( strcmp_P(oid, sysLocation ) == 0 ) {
      // handle sysLocation (set/get) requests
      if ( oPDU.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = oPDU.VALUE.decode(locLocation, strlen(locLocation)); 
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      } else {
        // response packet from get-request - locLocation
        iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_OCTETS, locLocation);
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
      //
    } else if (strcmp_P(oid, mibSensor0Temp ) == 0) {
       if ( oPDU.type == SNMP_PDU_GET ) {
        if(bHasTemp) {
          iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_INT, iSNMPTemp);
        }
        else {
          iSNMPError = SNMP_ERR_BAD_VALUE;
        }
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else if (strcmp_P(oid, mibSensor0Humid ) == 0) {
       if ( oPDU.type == SNMP_PDU_GET ) {
        if(bHasHumid) {
          iSNMPError = oPDU.VALUE.encode(SNMP_SYNTAX_INT, iSNMPHumid);
        }
        else {
          iSNMPError = SNMP_ERR_BAD_VALUE;
        }
        oPDU.type = SNMP_PDU_RESPONSE;
        oPDU.error = iSNMPError;
      }
    } else {
      // oid does not exist
      // response packet - object not found
      oPDU.type = SNMP_PDU_RESPONSE;
      oPDU.error = SNMP_ERR_NO_SUCH_NAME;
    }
    Agentuino.responsePdu(&oPDU);
  }
}

#endif
