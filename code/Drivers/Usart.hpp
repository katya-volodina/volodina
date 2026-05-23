#ifndef USART_HPP
#define USART_HPP

#include <string>
#include "iusart.hpp"

class Usart : public IUsart
{
public:
  Usart();
  void ConfigUSART() override;
  void SendMessage(const std::string& message) override;
};

#endif