#include "humidity.hpp"
#include <cmath> // for std::pow

Humidity::Humidity()
{
}

float Humidity::CalculateHumidity(float adcVoltageValue)
{
  //float percent = ((adcVoltageValue - minCalibrVoltage) / (maxCalibrVoltage - minCalibrVoltage)) * 100.0f;
  float percent = a3 * std::pow(adcVoltageValue, 3) + a2 * std::pow(adcVoltageValue, 2) + a1 * adcVoltageValue + a0;
  if (percent > 100.0f) 
    percent = 100.0f;
  return percent;
}