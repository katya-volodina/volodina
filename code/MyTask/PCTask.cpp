#include "pctask.hpp"

PCTask::PCTask(IDataProviders& variable, IUsart& usart, IFormatterUSART& formatter) :
  mVariable(variable),
  mUsart(usart),
  mFormatter(formatter)
{
}

void PCTask::Execute()
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