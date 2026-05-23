#include "measurementtask.hpp"

MeasurementTask::MeasurementTask(IFilter<float>& filter, 
                                 IMeasurementVariable& variable, 
                                 IHumidity& humidity, 
                                 IDataSetter& dataSetter) :
  mFilter(filter),
  mVariable(variable),
  mHumidity(humidity),
  mDataSetter(dataSetter)
{
}

void MeasurementTask::Execute()
{
  
  for(;;)
  {
    const auto measurementVariable = mVariable.Measure();
    auto filteredVoltage = mFilter.FilterValue(measurementVariable);
    auto MeasureHumidity = mHumidity.CalculateHumidity(filteredVoltage);
    mDataSetter.SetData(MeasureHumidity);
    Sleep(100ms);
  }
}