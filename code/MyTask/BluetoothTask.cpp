#include "bluetoothtask.hpp"

BluetoothTask::BluetoothTask(IDataProviders& variable, IUsart& usart, IFormatterUSART& formatter) :
  mVariable(variable),
  mUsart(usart),
  mFormatter(formatter)
{
}

void BluetoothTask::Execute()
{
  mUsart.ConfigUSART();
  for(;;)
  {
    const auto value = mVariable.GetData();
    std::string message = mFormatter.Format(value);
    mUsart.SendMessage(message);
    SleepUntil(1000ms);
  }
}