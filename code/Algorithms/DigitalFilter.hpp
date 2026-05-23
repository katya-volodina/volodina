#ifndef DIGITALFILTER_HPP
#define DIGITALFILTER_HPP

#include "ifilter.hpp" // for IFilter
#include <cmath> // for exp calculation

template<typename T, const T& dt, const T& rc>
class DigitalFilter : public IFilter<T>
{
public:
  using tValueType = T;
  
  DigitalFilter() : tau(static_cast<T>(1.0 - std::exp(-static_cast<double>(dt) / static_cast<double>(rc))))
  {
  }
  
  tValueType FilterValue(tValueType value) override
  {
    static bool isFirstTime = true;
    if(isFirstTime)
    {
      oldValue = value;
      isFirstTime = false;
      return value;
    }
    auto filteredValue = oldValue + (value - oldValue) * tau;
    oldValue = filteredValue;
    return filteredValue;
  }
  
private:
  tValueType oldValue{};
  const T tau;
};

#endif // DIGITALFILTER_HPP