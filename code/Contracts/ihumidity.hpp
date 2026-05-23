#ifndef IHUMIDITY_HPP
#define IHUMIDITY_HPP

class IHumidity
{
public:
  virtual float CalculateHumidity(float adcVoltageValue) = 0;
  virtual ~IHumidity() = default;
};

#endif // IHUMIDITY_HPP