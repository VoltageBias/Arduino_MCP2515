// Voltage Bias - the blog
// Gilbert Waltoon 
// 
// Released under a GNU General Public License v3.0 
// 
// FILENAME : Themistor_helper.cpp
// PURPOSE  : Arduino function to measure themperature from
//            a thermistor
//    
//
//  VERSION 0  15th October 2016 
//

#include "Thermistor_helper.h"
#include "Arduino.h"

/////////////////////////////////////////////////////////////
// define the function getThermistorTemperature()
float getThermistorTemperature(void) {
  float fTemperature;
  float fADCReading;
  float fThermistance; //thermistor resistance
 
  fADCReading = analogRead(THERMISTORPIN);
 
  // get the thermistor resistance from ADC reading
  fThermistance = BIAS_RESISTOR/((1023 / fADCReading)  - 1);

  // convert resistance to temperature using the Beta equation
  // see https://en.wikipedia.org/wiki/Thermistor

  fTemperature = fThermistance / R0;                      
  fTemperature = log(fTemperature);             
  fTemperature /= BCOEFFICIENT;                          // 1/Beta * ln(R/R0)
  fTemperature += 1.0 / (T0 + 273.15);                   // ...+ (1/To)
  fTemperature = 1.0 / fTemperature         ;            // ...invert
  fTemperature -= 273.15;                                // ...convert to 'C

  return fTemperature;
}
