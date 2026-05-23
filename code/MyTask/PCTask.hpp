#ifndef PCTASK_HPP
#define PCTASK_HPP

#include "thread.hpp"
#include "iusart.hpp"
#include "idataproviders.hpp"
#include "iformatterusart.hpp"

class PCTask : public OsWrapper::Thread<512U>
{
public:
  PCTask(IDataProviders& variable, IUsart& usart, IFormatterUSART& formatter);
  virtual void Execute() override;
  
private:
  IUsart& mUsart;
  IDataProviders& mVariable;
  IFormatterUSART& mFormatter;
};

#endif