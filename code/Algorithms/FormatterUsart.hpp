#ifndef FORMATTERUSART_HPP
#define FORMATTERUSART_HPP

#include "iformatterusart.hpp"
#include <sstream>
#include <iomanip>

class FormatterUSART : public IFormatterUSART
{
public:
  std::string Format(float value) override
  {
    std::ostringstream out;
    out << "Humidity: " << std::fixed << std::setprecision(2) << value << " %\r\n";
    return out.str();
  }
};

#endif