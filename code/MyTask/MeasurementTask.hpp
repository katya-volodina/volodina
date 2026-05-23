#ifndef MEASUREMENTTASK_HPP
#define MEASUREMENTTASK_HPP

#include "thread.hpp"
#include "ifilter.hpp"
#include "imeasurementvariable.hpp"
#include "ihumidity.hpp"
#include "idatasetter.hpp"
#include "AdcDmaDataProvider.hpp"

class MeasurementTask : public OsWrapper::Thread<512U>
{
public:
  MeasurementTask(IFilter<float>& filter, 
                  IMeasurementVariable& variable, 
                  IHumidity& humidity, 
                  IDataSetter& dataSetter);
  virtual void Execute() override;
  
private:
  IFilter<float>& mFilter;
  IMeasurementVariable& mVariable;
  
  IHumidity& mHumidity;
  IDataSetter& mDataSetter;
};

#endif