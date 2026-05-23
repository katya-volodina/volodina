#include "AdcDmaDataProvider.hpp"

AdcDmaDataProvider::AdcDmaDataProvider() : data(0)
{
  Config();
}

void AdcDmaDataProvider::ConfigDma()
{
  DMA2::S0CR::EN::Value0::Set();
  DMA2::S0CR::CHSEL::Value0::Set();
  DMA2::S0CR::CT::Value0::Set();
  DMA2::S0CR::DBM::Value0::Set();
  DMA2::S0CR::MSIZE::Value2::Set();
  DMA2::S0CR::PSIZE::Value2::Set();
  DMA2::S0CR::CIRC::Value1::Set();
  DMA2::S0CR::DIR::Value0::Set();
  DMA2::S0CR::PFCTRL::Value0::Set();

  *reinterpret_cast<volatile uint32_t*>(0x40026418) = ADC1::DR::Address;
  *reinterpret_cast<volatile uint32_t*>(0x4002641C) = reinterpret_cast<uint32_t>(&data);

  DMA2::S0NDTR::NDT::Set(1);
  DMA2::S0CR::EN::Value1::Set();
}

void AdcDmaDataProvider::Config()
{
  ConfigDma();
  ADC1::CR1::RES::Bits12::Set();
  ADC1::CR1::SCAN::Enable::Set();
  ADC1::CR2::CONT::ContinuousConversion::Set();
  ADC1::CR2::DMA::Enable::Set();
  ADC1::CR2::DDS::DMARequest::Set();

  ADC1::SQR3::SQ1::Set(0);

  ADC1::CR2::ADON::Enable::Set();
  ADC1::CR2::SWSTART::On::Set();
}

std::uint32_t AdcDmaDataProvider::GetData()
{
  return static_cast<std::uint32_t>(data);
}