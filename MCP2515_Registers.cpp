/* Voltage Bias - the Blog.
 * Gilbert Waltoon 
 * 
 * Released under a GNU General Public License v3.0 
 * 
 * FILENAME : MCP2515_Registers.cpp
 * PURPOSE  : UTILITIES FOR MCP2515 CAN CONTROLLER
 *    
 *
 *  VERSION 0 
 *
 *  
*/

#include "Arduino.h"
#include "SPI.h"
#include "MCP2515_Registers.h"

 //Reset the MCP2515
void resetIns(){
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(RESET_INS);
  delay(100);
  digitalWrite(chipSelectPin, HIGH);
  return;
}

 // Returns the value in the register addr 
byte readIns(tRegAddr addr){
  byte dataOut;
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)READ_INS);
  SPI.transfer((byte)addr);
  dataOut = SPI.transfer((byte)DONT_CARE); 
  digitalWrite(chipSelectPin, HIGH);
  return dataOut; 
}

//Fast read of MCP2515 RX buffer. Returns value read. 
//Possible arguments are READ_RXB0SIDH_INS, READ_RXB0D0_INS, READ_RXB1SIDH_INS, READ_RXB0D0_INS,
byte readRxBuffIns(tIns ins){
    byte dataOut;
    digitalWrite(chipSelectPin, LOW);
    SPI.transfer((byte)ins);
    dataOut = SPI.transfer((byte)DONT_CARE); 
    digitalWrite(chipSelectPin, HIGH);
    return dataOut;
 } 

//Write 'byte' to MCP2515 register 'tRegAddr'  
void writeIns(tRegAddr addr, byte dataIn){
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)WRITE_INS);
  SPI.transfer((byte)addr);
  SPI.transfer(dataIn); 
  digitalWrite(chipSelectPin, HIGH);
  return;
}

//Fast write of dataIn to the MCP2515 TX buffer. 
//Possible tIns arguments are LD_TXB0SIDH_INS, LD_TXB0D0_INS, LD_TXB1SIDH_INS, LD_TXB1D0_INS, LD_TXB2SIDH_INS  LD_TXB2D0_INS  
void ldTxBuffIns(tIns ins, byte dataIn){
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)ins);
  SPI.transfer(dataIn); 
  digitalWrite(chipSelectPin, HIGH);
  return;
}

//Request MCP2515 to send the message sitting in trasmit-buffer 'tIns'. 
void rqstToSendIns(tIns ins){
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)ins);
  digitalWrite(chipSelectPin, HIGH);
  return;
}

 //Modify register bits. 1st argument is register. 2nd argument is the bits to modify. 3rd argument is new bit values to write.
void bitModifyIns(tRegAddr addr, tMask mask, tMask setBits){
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)BIT_MODIFY_INS);
  SPI.transfer((byte)addr);
  SPI.transfer((byte)mask);
  SPI.transfer((byte)setBits);
  digitalWrite(chipSelectPin, HIGH);
  return;
}

//Fast access to selected register bits.
byte readStatusIns(){
  byte dataOut;
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)READ_STATUS_INS);
  dataOut=SPI.transfer((byte)DONT_CARE);
  digitalWrite(chipSelectPin, HIGH);
  return dataOut;
}

// Fast access to status information on messages received.
byte rxStatusIns(){
  byte dataOut;
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer((byte)RX_STATUS_INS);
  dataOut=SPI.transfer((byte)DONT_CARE);
  digitalWrite(chipSelectPin, HIGH);
  return dataOut;
 }
 
//Print list of CAN errors on serial port. Returns TRUE is errors occurred.
 bool check4Errs(){
      // read error flag register and print out any errors
      // return false if no errors
      byte eFlgByte;
      eFlgByte = readIns(EFLG); 
      if(eFlgByte) {
        Serial.println("!!!!!!!!!!! Error reported by EFLG register !!!!!!!!!!!!");
        if(eFlgByte & EWARN)  Serial.println("EWARN WAS SET: >=96 errors in TEC or REC"); 
        if(eFlgByte & RXWAR)  Serial.println("RXWAR WAS SET: >=96 errors in REC");
        if(eFlgByte & TXWAR)  Serial.println("TXWAR WAS SET: >=96 errors in TEC");
        if(eFlgByte & RXEP)   Serial.println("RXEP WAS SET: >=128 errors in REC");
        if(eFlgByte & TXEP)   Serial.println("TXEP WAS SET: >=128 errors in REC");
        if(eFlgByte & TXBO)   Serial.println("TXBO WAS SET: TEC reached 255; BUS OFF");
        if(eFlgByte & RX0OVR) Serial.println("RX0OVR WAS SET: RECEIVE BUFFER_0 OVERFLOWED");
        if(eFlgByte & RX1OVR) Serial.println("RX1OVR WAS SET: RECEIVE BUFFER_1 OVERFLOWED");
        Serial.print("TX ERROR COUNT="); Serial.print("\t"); Serial.println( readIns(TEC) );
        Serial.print("RX ERROR COUNT="); Serial.print("\t"); Serial.println( readIns(REC) );
        Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        Serial.println( );
        return true;
      }
      Serial.println( "No errors");
      return false;      
 }

 //Select MCP2515 mode. Possible arguments are "Normal" "Sleep" "Loopback" "Listen" "Configuration". Returns TRUE if successful.
      bool setMode(String szMode){
      
      
          if 
             (szMode == "Normal")       {
                                           bitModifyIns(CANCTRL, REQOP2|REQOP1|REQOP0, 0); 
                                           Serial.println("Entering mode: NORMAL");
                                           return true; 
                                         }
           else if
              (szMode == "Sleep")        {
                                           bitModifyIns(CANCTRL, REQOP2|REQOP1|REQOP0, REQOP0); 
                                           Serial.println("Entering mode: SLEEP");
                                           return true; 
                                         }
           else if
              (szMode == "Loopback")     {
                                           bitModifyIns(CANCTRL, REQOP2|REQOP1|REQOP0, REQOP1); 
                                           Serial.println("Entering mode: LOOPBACK");
                                           return true; 
                                         }
           else if
              (szMode == "Listen")       {
                                            bitModifyIns(CANCTRL, REQOP2|REQOP1|REQOP0, REQOP1|REQOP0); 
                                            Serial.println("Entering mode: LISTEN");
                                            return true; 
                                         }
           else if
              (szMode == "Configuration"){
                                           bitModifyIns(CANCTRL, REQOP2|REQOP1|REQOP0, REQOP1|REQOP2); 
                                            Serial.println("Entering mode: CONFIGURATION");
                                           return true; 
                                          }
           else                {
                                 Serial.println ("Mode wasn't recognised in call to function setMode(mode)");
                                 return false;
                                 }

      }

