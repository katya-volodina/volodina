#ifndef IUSART_HPP
#define IUSART_HPP

#include <string>

class IUsart
{
public:
  virtual void SendMessage(const std::string& message) = 0;
  virtual void ConfigUSART() = 0;
  virtual ~IUsart() = default;
};

#endif