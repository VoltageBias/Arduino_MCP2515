/* Voltage Bias - the Blog.
 * Gilbert Waltoon 
 * 
 * Released under a GNU General Public License v3.0 
 * 
 * FILENAME: MCP2515_Registers.h
 * PURPOSE: REGISTERS AND UTILITIES FOR MCP2515 CAN CONTROLLER
 *    
 *
 *  VERSION 0
 *  VERSION 1     21May2016  
 *               - Added check4Errs() function
 *               - Modified readStatusIns() and rxStatusIns() to remove second (repeated) read
 *  
*/

// Define CS pin for SPI
#define chipSelectPin 7

// Define some common data types
typedef const byte tRegAddr;  
typedef const byte tMask;
typedef const byte tIns;
typedef const byte tBitMask;

 
//Foward declaration of handy MCP2515 functions/utlities.
//See the SPI-Interface section of the MCP2515 datasheet for full details.

  void resetIns();                            //Reset the MCP2515
  byte readIns(tRegAddr);                     //Read an MCP2515 register. Returns the value in the register 'tRegAddr' 
  byte readRxBuffIns(tIns);                   //Fast read of MCP2515 RX buffer. Returns value read. Possible arguments are READ_RXB0SIDH_INS, READ_RXB0D0_INS, READ_RXB1SIDH_INS, READ_RXB0D0_INS  
  void writeIns(tRegAddr, byte);              //Write 'byte' to MCP2515 register 'tRegAddr'
  void ldTxBuffIns(tIns, byte);               //Fast write of 'byte' to the MCP2515 TX buffer. Possible 'tIns' arguments are LD_TXB0SIDH_INS, LD_TXB0D0_INS, LD_TXB1SIDH_INS, LD_TXB1D0_INS, LD_TXB2SIDH_INS  LD_TXB2D0_INS  
  void rqstToSendIns(tIns);                   //Request MCP2515 to send the message sitting in trasmit-buffer 'tIns'. 
  void bitModifyIns(tRegAddr, tMask, tMask);  //Modify register bits. 1st argument is register. 2nd argument is the bits to modify. 3rd argument is new bit values to write.
  byte readStatusIns();                       //Fast access to selected register bits.
  byte rxStatusIns();                         //Fast access to status information on messages received.
  bool check4Errs();                          //Print list of CAN errors on serial port. Returns TRUE is errors occurred.
  bool setMode(String);                       //Select MCP2515 mode. Possible arguments are "Normal" "Sleep" "Loopback" "Listen" "Configuration". Returns TRUE if successful.

/*
 * *****************************************************
 * MCP2515 Registers follow
 */
tRegAddr RXF0SIDH  = 0b00000000;
tRegAddr RXF0SIDL  = 0b00000001;
tRegAddr RXF0EIDB  = 0b00000010;
tRegAddr RXF0EID0  = 0b00000011;
tRegAddr RXF1SIDH  = 0b00000100;
tRegAddr RXF1SIDL  = 0b00000101;
tRegAddr RXF1EID8  = 0b00000110;
tRegAddr RXF1EID0  = 0b00000111;
tRegAddr RXF2SIDH  = 0b00001000;
tRegAddr RXF2SIDL  = 0b00001001;
tRegAddr RXF2EID8  = 0b00001010;
tRegAddr RXF2EID0  = 0b00001011;
tRegAddr BFPCTRL   = 0b00001100;
tRegAddr TXRTSCTRL = 0b00001101;
tRegAddr CANSTAT   = 0b00001110;
tRegAddr CANCTRL   = 0b00001111;

tRegAddr  RXF3SIDH  = 0b00010000;
tRegAddr  RXF3SIDL  = 0b00010001;
tRegAddr  RXF3EIDB  = 0b00010010;
tRegAddr  RXF3EID0  = 0b00010011;
tRegAddr  RXF4SIDH  = 0b00010100;
tRegAddr  RXF4SIDL  = 0b00010101;
tRegAddr  RXF4EID8  = 0b00010110;
tRegAddr  RXF4EID0  = 0b00010111;
tRegAddr  RXF5SIDH  = 0b00011000;
tRegAddr  RXF5SIDL  = 0b00011001;
tRegAddr  RXF5EID8  = 0b00011010;
tRegAddr  RXF5EID0  = 0b00011011;
tRegAddr  TEC       = 0b00011100;
tRegAddr  REC       = 0b00011101;

tRegAddr  RXM0SIDH  = 0b00100000;
tRegAddr  RXM0SIDL  = 0b00100001;
tRegAddr  RXM0EIDB  = 0b00100010;
tRegAddr  RXM0EID0  = 0b00100011;
tRegAddr  RXM1SIDH  = 0b00100100;
tRegAddr  RXM1SIDL  = 0b00100101;
tRegAddr  RXM1EID8  = 0b00100110;
tRegAddr  RXM1EID0  = 0b00100111;
tRegAddr  CANF3     = 0b00101000;
tRegAddr  CANF2     = 0b00101001;
tRegAddr  CANF1     = 0b00101010;
tRegAddr  CANINTE   = 0b00101011;
tRegAddr  CANINTF   = 0b00101100;
tRegAddr  EFLG      = 0b00101101;

tRegAddr  TXB0CTRL  = 0b00110000;
tRegAddr  TXB0SIDH  = 0b00110001;
tRegAddr  TXB0SIDL  = 0x32;
tRegAddr  TXB0EIDB  = 0b00110011;
tRegAddr  TXB0EID0  = 0b00110100;
tRegAddr  TXB0DLC   = 0b00110101;
tRegAddr  TXB0D0    = 0b00110110;
tRegAddr  TXB0D1    = 0b00110111;
tRegAddr  TXB0D2    = 0b00111000;
tRegAddr  TXB0D3    = 0b00111001;
tRegAddr  TXB0D4    = 0b00111010;
tRegAddr  TXB0D5    = 0b00111011;
tRegAddr  TXB0D6    = 0b00111100;
tRegAddr  TXB0D7    = 0b00111101;

tRegAddr  TXB1CTRL  = 0b01000000;
tRegAddr  TXB1SIDH  = 0b01000001;
tRegAddr  TXB1SIDL  = 0b01000010;
tRegAddr  TXB1EIDB  = 0b01000011;
tRegAddr  TXB1EID0  = 0b01000100;
tRegAddr  TXB1DLC   = 0b01000101;
tRegAddr  TXB1D0    = 0b01000110;
tRegAddr  TXB1D1    = 0b01000111;
tRegAddr  TXB1D2    = 0b01001000;
tRegAddr  TXB1D3    = 0b01001001;
tRegAddr  TXB1D4    = 0b01001010;
tRegAddr  TXB1D5    = 0b01001011;
tRegAddr  TXB1D6    = 0b01001100;
tRegAddr  TXB1D7    = 0b01001101;

tRegAddr  TXB2CTRL  = 0b01010000;
tRegAddr  TXB2SIDH  = 0b01010001;
tRegAddr  TXB2SIDL  = 0b01010010;
tRegAddr  TXB2EIDB  = 0b01010011;
tRegAddr  TXB2EID0  = 0b01010100;
tRegAddr  TXB2DLC   = 0b01010101;
tRegAddr  TXB2D0    = 0b01010110;
tRegAddr  TXB2D1    = 0b01010111;
tRegAddr  TXB2D2    = 0b01011000;
tRegAddr  TXB2D3    = 0b01011001;
tRegAddr  TXB2D4    = 0b01011010;
tRegAddr  TXB2D5    = 0b01011011;
tRegAddr  TXB2D6    = 0b01011100;
tRegAddr  TXB2D7    = 0b01011101;

tRegAddr  RXB0CTRL  = 0b01100000;
tRegAddr  RXB0SIDH  = 0b01100001;
tRegAddr  RXB0SIDL  = 0b01100010;
tRegAddr  RXB0EIDB  = 0b01100011;
tRegAddr  RXB0EID0  = 0b01100100;
tRegAddr  RXB0DLC   = 0b01100101;
tRegAddr  RXB0D0    = 0b01100110;
tRegAddr  RXB0D1    = 0b01100111;
tRegAddr  RXB0D2    = 0b01101000;
tRegAddr  RXB0D3    = 0b01101001;
tRegAddr  RXB0D4    = 0b01101010;
tRegAddr  RXB0D5    = 0b01101011;
tRegAddr  RXB0D6    = 0b01101100;
tRegAddr  RXB0D7    = 0b01101101;

tRegAddr  RXB1CTRL  = 0b01110000;
tRegAddr  RXB1SIDH  = 0b01110001;
tRegAddr  RXB1SIDL  = 0b01110010;
tRegAddr  RXB1EIDB  = 0b01110011;
tRegAddr  RXB1EID0  = 0b01110100;
tRegAddr  RXB1DLC   = 0b01110101;
tRegAddr  RXB1D0    = 0b01110110;
tRegAddr  RXB1D1    = 0b01110111;
tRegAddr  RXB1D2    = 0b01111000;
tRegAddr  RXB1D3    = 0b01111001;
tRegAddr  RXB1D4    = 0b01111010;
tRegAddr  RXB1D5    = 0b01111011;
tRegAddr  RXB1D6    = 0b01111100;
tRegAddr  RXB1D7    = 0b01111101;

tRegAddr CNF3       =0x28;
tRegAddr CNF2       =0x29;
tRegAddr CNF1       =0x2A;
/*
 * *****************************************************
 * end MCP2515 Registers
 */

/*
 * *****************************************************
 * MASK bytes follow
 */


 // BFPCTRL
tMask B1BFS  = 0b00100000;
tMask B0BFS  = 0b00010000;
tMask B1BFE  = 0b00001000;
tMask B0BFE  = 0b00000100;
tMask B1BFM  = 0b00000010;
tMask B0BFM  = 0b00000001;

// TXRTSCTRL
tMask B2RTS  = 0b00100000;
tMask B1RTS  = 0b00010000;
tMask B0RTS  = 0b00001000;
tMask B2RTSM = 0b00000100;
tMask B1RTSM = 0b00000010;
tMask B0RTSM = 0b00000001;

// CANSTAT
tMask OPMOD2 = 0b10000000;
tMask OPMOD1 = 0b01000000;
tMask OPMOD0 = 0b00100000;
tMask ICOD2  = 0b00001000;
tMask ICOD1  = 0b00000100;
tMask ICOD0  = 0b00000010;

// CANCTRL
tMask REQOP2   = 0b10000000;
tMask REQOP1   = 0b01000000;
tMask REQOP0   = 0b00100000;
tMask ABAT     = 0b00010000;
tMask OSM      = 0b00001000;
tMask CLKEN    = 0b00000100;
tMask CLKPRE1  = 0b00000010;
tMask CLKPRE0  = 0b00000001;

// CNF3
tMask SOF     = 0b10000000;
tMask WAKFIL  = 0b01000000;
tMask PHSEG22 = 0b00000100;
tMask PHSEG21 = 0b00000010;
tMask PHSEG20 = 0b00000001;

// CANF2
tMask BTLMODE  = 0b10000000;
tMask SAM      = 0b01000000;
tMask PHSEG12  = 0b00100000;
tMask PHSEG11  = 0b00010000;
tMask PHSEG10  = 0b00001000;
tMask PHSEG2   = 0b00000100;
tMask PHSEG1   = 0b00000010;
tMask PHSEG0   = 0b00000001;

// CANF1
tMask SJW1   = 0b10000000;
tMask SJW0   = 0b01000000;
tMask BRP5   = 0b00100000;
tMask BRP4   = 0b00010000;
tMask BRP3   = 0b00001000;
tMask BRP2   = 0b00000100;
tMask BRP1   = 0b00000010;
tMask BRP0   = 0b00000001;

// CANINTE
tMask MERRE   = 0b10000000;
tMask WAKIE   = 0b01000000;
tMask ERRIE   = 0b00100000;
tMask TX2IE   = 0b00010000;
tMask TX1IE   = 0b00001000;
tMask TX0IE   = 0b00000100;
tMask RX1IE    = 0b00000010;
tMask RX0IE    = 0b00000001;

// CANINTF
tMask MERRF   = 0b10000000;
tMask WAKIF   = 0b01000000;
tMask ERRIF   = 0b00100000;
tMask TX2IF   = 0b00010000;
tMask TX1IF   = 0b00001000;
tMask TX0IF   = 0b00000100;
tMask RX1IF   = 0b00000010;
tMask RX0IF   = 0b00000001;

// EFLG
tMask RX1OVR   = 0b10000000;
tMask RX0OVR   = 0b01000000;
tMask TXBO     = 0b00100000;
tMask TXEP     = 0b00010000;
tMask RXEP     = 0b00001000;
tMask TXWAR    = 0b00000100;
tMask RXWAR    = 0b00000010;
tMask EWARN    = 0b00000001;

// TXB0CTRL, TXB1CTRL, TXB2CTRL, 
tMask ABTF     = 0b01000000;
tMask MLOA     = 0b00100000;
tMask TXERR    = 0b00010000;
tMask TXREQ    = 0b00001000;
tMask TXP1     = 0b00000010;
tMask TXP0     = 0b00000001;

// RXB0CTRL
tMask RXM1     = 0b01000000;
tMask RXM0     = 0b00100000;
tMask RXRTR    = 0b00001000;
tMask BUKT     = 0b00000100;
tMask BUKT1    = 0b00000010;
tMask FILHIT0  = 0b00000001;
// RXB1CTRL
tMask FILHIT2  = 0b00000100;
tMask FILHIT1  = 0b00000010;


//other bit masks - these are not settable using BitModift - hence different type
//TXBnSIDH
tBitMask SID10    = 0b10000000;
tBitMask SID9     = 0b01000000;
tBitMask SID8     = 0b00100000;
tBitMask SID7     = 0b00010000;
tBitMask SID6     = 0b00001000;
tBitMask SID5     = 0b10000100;
tBitMask SID4     = 0b10000010;
tBitMask SID3     = 0b10000001;
//TXBnSIDL
tBitMask SID2     = 0b10000000;
tBitMask SID1     = 0b01000000;
tBitMask SID0     = 0b00100000;
tBitMask EXIDE    = 0b00001000;
tBitMask EID17    = 0b00000010;
tBitMask EID16    = 0b00000001;
//TXBnDLC
tBitMask RTR      = 0b01000000;
tBitMask DLC3     = 0b00001000;
tBitMask DLC2     = 0b10000100;
tBitMask DLC1     = 0b10000010;
tBitMask DLC0     = 0b10000001;


/*
 * *****************************************************
 *  INSTRUCTION constants follow - see datasheet section describing SPI Intruction Set
 */

tIns DONT_CARE              = 0b11111111;
tIns RESET_INS              = 0b11000000;      // MCP2515 reset instruction
tIns READ_INS               = 0b00000011;      // MCP2515 read data from register beginning at selected address
tIns READ_RXB0SIDH_INS      = 0b10010000;      // Receive Buffer 0. Start at RXB0SIDH(61h)= 8 MSBs of the received msg identifier
tIns READ_RXB0D0_INS        = 0b10010010;      // Receive Buffer 0. Start at RXB0D0(66h)  = Byte0 of eight possible message bytes
tIns READ_RXB1SIDH_INS      = 0b10010100;      // Receive Buffer 1. Start at RXB0SIDH(71h)= 8 MSBs of the received msg identifier
tIns READ_RXB1D0_D0_INS     = 0b10010110;      // Receive Buffer 1. Start at RXB0D0(76h)  = Byte0 of eight possible message bytes
tIns WRITE_INS              = 0b00000010;      // Write data at selected address
tIns LD_TXB0SIDH_INS        = 0b01000000;      // Load TX Buffer 0, Start at address TXB0SIDH(31h)
tIns LD_TXB0D0_INS          = 0b01000001;
tIns LD_TXB1SIDH_INS        = 0b01000010;
tIns LD_TXB1D0_INS          = 0b01000011;
tIns LD_TXB2SIDH_INS        = 0b01000100;
tIns LD_TXB2D0_INS          = 0b01000101;
tIns RTS_T0_INS             = 0b10000001;
tIns RTS_T1_INS             = 0b10000010;
tIns RTS_T2_INS             = 0b10000100;
tIns RTS_T0T1_INS           = 0b10000011;
tIns RTS_T0T2_INS           = 0b10000101;
tIns RTS_T1T2_INS           = 0b10000110;
tIns RTS_T0T1T2_INS         = 0b10000111;
tIns READ_STATUS_INS        = 0b10100000;
tIns RX_STATUS_INS          = 0b10110000;
tIns BIT_MODIFY_INS         = 0b00000101;

/*
 * *****************************************************
 * end INSTRUCTION constants definitions
 */
 /*
***************************************
*/



