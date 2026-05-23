#ifndef VOLTAGE_HPP
#define VOLTAGE_HPP

#include "idataprovider.hpp" // for IDataProvider
#include "imeasurementvariable.hpp" // for IMeasurementVariable

template<const float& gain, const float& offset>
class Voltage : public IMeasurementVariable
{
public:
  Voltage(IDataProvider& data) : mData(data)
  {
  }
  
  float Measure() override
  {
    auto voltageValue = gain * (static_cast<float>(mData.GetData())) + offset;
    return voltageValue;
  }
  
private:
  IDataProvider& mData;
};

#endif // VOLTAGE_HPP