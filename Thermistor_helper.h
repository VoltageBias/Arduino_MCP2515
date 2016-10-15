// Voltage Bias - the blog
// Gilbert Waltoon 
// 
// Released under a GNU General Public License v3.0 
// 
// FILENAME : Themistor_helper.h
// PURPOSE  : Arduino utility to measure themperature from
//            a thermistor
//    
//
//  VERSION 0  15th October 2016 
//
//  
//

// Input pin for thermistor voltage measurement
#define THERMISTORPIN A5

// the value of the bias resistor
#define BIAS_RESISTOR 9926

 //beta of thermistor 
#define BCOEFFICIENT 3933 //RComponents, type 151-237

// thermistor resistance R0 from datasheet
#define R0 10000 

//...at temperature
#define T0 25

//declare the function we'll use
float getThermistorTemperature(void);
