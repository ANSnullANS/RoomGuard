#ifdef SNMP_ENABLED
#include <Streaming.h>

char aResponse[64];

void pduReceived()
{
  SNMP_PDU pdu;
  iSNMPStatus = Agentuino.requestPdu(&pdu);
  
  if ((pdu.type == SNMP_PDU_GET || pdu.type == SNMP_PDU_GET_NEXT || pdu.type == SNMP_PDU_SET)
    && pdu.error == SNMP_ERR_NO_ERROR && iSNMPStatus == SNMP_API_STAT_SUCCESS ) {
    //
    pdu.OID.toString(oid);

    #ifdef DEBUG
      Serial.print("SNMP Req. ");
      Serial.println(oid);
    #endif
    
    if ( strcmp_P(oid, sysDescr ) == 0 ) {
      // handle sysDescr (set/get) requests
      if ( pdu.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read-only
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = SNMP_ERR_READ_ONLY;
      } else {
        // response packet from get-request - locDescr
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, locDescr);
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      }
      //
    } else if (strcmp_P(oid, mibSSID) == 0) { // SSID Requested
      if ( pdu.type == SNMP_PDU_GET ) {
        // Convert SSID to OCTETS and send back.
        sSSID.toCharArray(aResponse, 64);
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, aResponse);
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      }
    } else if ( strcmp_P(oid, sysUpTime ) == 0 ) {
      // handle sysName (set/get) requests
      if ( pdu.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read-only
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = SNMP_ERR_READ_ONLY;
      } else {
        // response packet from get-request - locUpTime
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_TIME_TICKS, locUpTime);       
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
        #ifdef DEBUG
          Serial.print(pdu.type);
          Serial.print(" / ");
          Serial.println(pdu.error);
        #endif
      }
      //
    } else if ( strcmp_P(oid, sysName ) == 0 ) {
      // handle sysName (set/get) requests
      if ( pdu.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = pdu.VALUE.decode(locName, strlen(locName)); 
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      } else {
        // response packet from get-request - locName
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, locName);
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      }
      //
    } else if ( strcmp_P(oid, sysContact ) == 0 ) {
      // handle sysContact (set/get) requests
      if ( pdu.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = pdu.VALUE.decode(locContact, strlen(locContact)); 
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      } else {
        // response packet from get-request - locContact
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, locContact);
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      }
      //
    } else if ( strcmp_P(oid, sysLocation ) == 0 ) {
      // handle sysLocation (set/get) requests
      if ( pdu.type == SNMP_PDU_SET ) {
        // response packet from set-request - object is read/write
        iSNMPError = pdu.VALUE.decode(locLocation, strlen(locLocation)); 
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      } else {
        // response packet from get-request - locLocation
        iSNMPError = pdu.VALUE.encode(SNMP_SYNTAX_OCTETS, locLocation);
        pdu.type = SNMP_PDU_RESPONSE;
        pdu.error = iSNMPError;
      }
      //
    } else {
      // oid does not exist
      // response packet - object not found
      pdu.type = SNMP_PDU_RESPONSE;
      pdu.error = SNMP_ERR_NO_SUCH_NAME;
    }
    Agentuino.responsePdu(&pdu);
  }
}

#endif