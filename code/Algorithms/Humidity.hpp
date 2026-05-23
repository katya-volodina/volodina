#ifndef HUMIDITY_HPP
#define HUMIDITY_HPP

#include "ihumidity.hpp" // for IHumidity
#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC

class Humidity : public IHumidity
{
public:
  Humidity();
  float CalculateHumidity(float adcVoltageValue) override;
private:                       
  const float maxCalibrVoltage = 1.894f;
  const float minCalibrVoltage = 0.0f;
  const float a3 = -2.213f;
  const float a2 = 5.353f;
  const float a1 = 49.275f;
  const float a0 = 0.011f;
};

#endif // HUMIDITY_HPP