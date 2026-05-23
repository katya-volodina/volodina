#ifndef BLUETOOTHTASK_HPP
#define BLUETOOTHTASK_HPP

#include "thread.hpp"
#include "iusart.hpp"
#include "idataproviders.hpp"
#include "iformatterusart.hpp"

class BluetoothTask : public OsWrapper::Thread<512U>
{
public:
  BluetoothTask(IDataProviders& variable, IUsart& usart, IFormatterUSART& formatter);
  virtual void Execute() override;
  
private:
  IUsart& mUsart;
  IDataProviders& mVariable;
  IFormatterUSART& mFormatter;
};

#endif