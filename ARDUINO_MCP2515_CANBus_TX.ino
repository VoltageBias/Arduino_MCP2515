// VoltageBias - the Blog
//  Gilbert Waltoon
//  
//  Released under a GNU General Public License v3.0 
//  
//  FILENAME : ARDUINO_MCP2515_CANBus_TX
//  
//  PURPOSE : Sends temperature data from Arduino Uno via CANBus.
//            Uses Microchip MCP2515 CAN transceiver IC.
//            See VoltageBias - the blog, for full details.
// 
//   VERSION 0: 4 Oct 2016
//   VERSION 1: 15 Oct 2016. Minor mods. to serial monitor msgs
//
// 
//  Arduino hook-up guide:
//  SPI CS :  Uno pin 7 (selectable) - see file MCP2515_Registers.h    
//  SPI MOSI: Uno pin 11             
//  SPI MISO: Uno pin 12                  
//  SPI SCK:  Uno pin 13                  
//  Power rail etting : 5V
//
//  ******************************************************************
//    SETTINGS - Change me!!!!!
//
#define RESET_ON_RESTART (true) // Reset MCP2515 when Sketch restarts
#define CNF1_TIMING      (0x01) // Using 8MHz-Xtal on NiREN board so
#define CNF2_TIMING      (0x9A) // set MCP2515 CAN timing registers
#define CNF3_TIMING      (0x07) // accordingly.
//See https://www.kvaser.com/support/calculators/bit-timing-calculator/ 
// **********************************************************************
//
//  Globals and Includes 
#include <SPI.h>
#include "MCP2515_Registers.h"
#include "Thermistor_helper.h"
int msgData =0;    // will contain the message data to be transmitted.
int msgSID  =0;    // will contain CAN-message identifiers.
// *******************************************************
// Sketch setup...
void setup() {
pinMode(chipSelectPin, OUTPUT);
//Start the Serial monitor
Serial.begin(9600);
//I nitialise the SPI link to thr MCP2515
SPI.begin();
SPI.beginTransaction(SPISettings(1400000, MSBFIRST, SPI_MODE0));
/*
     140 000 000 here gives Sck period c.120ns i.e. 8MHz
     14 000 000      gives Sck           1us   i.e. 1MHz
     SPI_MODE0 corresponds to CPOL 0, CPHA 0
     SPI_MODE1 corresponds to CPOL 0, CPHA 1
  */
if (RESET_ON_RESTART) {
Serial.println("Resetting");
resetIns();  //call reset function (see MCP2515_Registers.h)
}
// Enter MCP2515 configuration mode using setMode()
// function defined in MCP2515_Registers.h,
// and set up CAN bit timing registers.
while ( !setMode("Configuration") ) {};
writeIns(CNF1, CNF1_TIMING);
writeIns(CNF2, CNF2_TIMING);
writeIns(CNF3, CNF3_TIMING);
// Bit timing registers above are write-protected 
// outside of 'Configuration' mode so, for safety, 
// check they were successfully modified
while ( readIns(CNF1) != CNF1_TIMING ) {
Serial.println("Failed to write to CNF1");
delay(999999);
}
while ( readIns(CNF2) != CNF2_TIMING ) {
Serial.println("Failed to write to CNF2");
delay(999999);
}
while ( readIns(CNF2) != CNF2_TIMING ) {
Serial.println("Failed to write to CNF3");
delay(999999);
}
// Set MCP2515 mode to normal operation
while ( !setMode("Normal") ) {};
// Abort any pending transmissions
// by setting the ABAT bit of the CANCTL register
bitModifyIns(CANCTRL, ABAT, ABAT);
// Clear the abort-transmission instruction above
bitModifyIns(CANCTRL, ABAT, 0b00000000);
//Load TXB0SIDH transmission register with 0's
ldTxBuffIns(LD_TXB0SIDH_INS, 0x0);
//Set CAN frames as Data frames of 1 byte by
//configuring TXB0DLC register.
writeIns(TXB0DLC, readIns(TXB0DLC) & (~RTR) & (~DLC3) & 
(~DLC2) & (~DLC1) | DLC0 );
//Don't trigger interrupts upon transmission
bitModifyIns(CANINTE, TX0IE, ~TX0IE);
//Configure RXB0 receiver to accept al1 messages
bitModifyIns(RXB0CTRL, RXM1 | RXM0, RXM1 | RXM0);
//Don't use pins for interrupts
bitModifyIns(BFPCTRL, B0BFM, ~B0BFM);
//Don't use RX interrupts
bitModifyIns(CANINTE, RX0IE, ~RX0IE);
//Clear any 'RXBuffer full' interrupts
bitModifyIns(CANINTF, RX0IF, ~RX0IF);
Serial.println("Completed setup");
Serial.println("***************");
Serial.println();
}
//  end of setup()
// **********************************************
// *********************************************
//    Main Sketch loop...  
void loop() {
//get some temperature data to act as message data
msgData = getThermistorTemperature();

//Load TXB0 buffer with message data 
ldTxBuffIns(LD_TXB0D0_INS, msgData);

// Set CAN message ID to value of msgData,
// and set EIXDE = 0 (=standard, non-extended, identifer)
writeIns(TXB0SIDL, ( readIns(TXB0SIDL) & (~EXIDE) & (~SID0) & 
(~SID1) & (~SID2) ) | (msgSID << 5) );

//Request TXB0 CAN buffer to send its data
rqstToSendIns(RTS_T0_INS);

//Print some status info. to the  serial monitor                     
Serial.print("Arduino sending temperature="); Serial.print(msgData); 
Serial.print("\t"); Serial.print("With CAN ID="); 
Serial.println(msgSID);

//wait for message to go
delay(100);
// call check4Errs() (see Registers.h)
// to print any errors on serial monitor.
check4Errs();
//increment the message ID 
msgSID = (msgSID + 1) % 8;
//wait a bit, then loop.
delay(2000);
}
// END
// *************************
