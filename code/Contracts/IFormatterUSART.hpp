#ifndef IFORMATTERUSART_HPP
#define IFORMATTERUSART_HPP

#include <string>

class IFormatterUSART
{
public:
  virtual std::string Format(float value) = 0;
  virtual ~IFormatterUSART() = default;
};

#endif