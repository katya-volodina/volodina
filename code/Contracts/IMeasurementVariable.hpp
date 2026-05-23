#ifndef IMEASUREMENTVARIABLE_HPP
#define IMEASUREMENTVARIABLE_HPP

class IMeasurementVariable
{
public:
  virtual float Measure() = 0;
  virtual ~IMeasurementVariable() = default;
};

#endif // IMEASUREMENTVARIABLE_HPP