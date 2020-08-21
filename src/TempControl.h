#include <Arduino.h>
#include <FS.h>  

#define ntc A0

const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
const double R2 = 11000;            // 10k ohm series resistor
const double adc_resolution = 1023; // 10-bit adc

const double A = 0.001129148;   // thermistor equation parameters
const double B = 0.000234125;
const double C = 0.0000000876741; 

double Vout, Rth, temperature, adc_value; 

double Temp(double AnalogRead){
  adc_value = AnalogRead;
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;

/*  Steinhart-Hart Thermistor Equation:
 *  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
 *  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperature in kelvin

  temperature = temperature - 273.15;  // Temperature in degree celsius
  Serial.println("Temp = " + String(temperature));
  return temperature;
}