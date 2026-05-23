#include <cstddef>
#include <cmath>
#include "usart.hpp"
#include "gpioaregisters.hpp"
#include "usart2registers.hpp"

Usart::Usart()
{
}

void Usart::ConfigUSART()
{
  GPIOA::MODER::MODER3::Alternate::Set();
  GPIOA::MODER::MODER2::Alternate::Set();
  GPIOA::AFRL::AFRL3::Af7::Set();
  GPIOA::AFRL::AFRL2::Af7::Set();
  GPIOA::PUPDR::PUPDR2::NoPullUpNoPullDown::Set();
  GPIOA::PUPDR::PUPDR3::PullUp::Set();
  
  USART2::CR1::OVER8::OversamplingBy16::Set();
  USART2::CR1::M::Data8bits::Set();
  USART2::CR2::STOP::Value0::Set();
  USART2::CR1::PCE::ParityControlDisable::Set();
  USART2::CR1::RE::Enable::Set();
  USART2::CR1::RXNEIE::InterruptWhenRXNE::Set();
  
  constexpr std::uint32_t SystemCoreClock = 16'000'000U;
  constexpr std::uint32_t BaudRate = 9600;
  double UsartDivDouble = (static_cast<double>(SystemCoreClock) / (BaudRate * 16.0));
  uint32_t UsartDivMantissa = static_cast<uint32_t>(UsartDivDouble);
  uint16_t UsartDivFraction = static_cast<uint16_t>(std::round((UsartDivDouble - UsartDivMantissa) * 16));
  
  USART2::BRR::DIV_Mantissa::Set(UsartDivMantissa);
  USART2::BRR::DIV_Fraction::Set(UsartDivFraction);
  USART2::CR1::UE::Enable::Set();
  USART2::SR::TC::TransmitionNotComplete::Set();
}

void Usart::SendMessage(const std::string& message)
{
  std::size_t i = 0;
  while(i < message.length())
  {
    while(!USART2::SR::TXE::DataRegisterEmpty::IsSet())
    {
    }
    USART2::DR::Write(static_cast<uint8_t>(message[i++]));
  }
}