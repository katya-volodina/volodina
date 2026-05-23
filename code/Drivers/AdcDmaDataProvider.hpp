#ifndef ADCDMADATAPROVIDER_HPP
#define ADCDMADATAPROVIDER_HPP

#include "adc1registers.hpp"
#include "adccommonregisters.hpp"
#include "dma2registers.hpp"
#include "idataprovider.hpp"

class AdcDmaDataProvider : public IDataProvider
{
public:
  AdcDmaDataProvider();
  void Config();
  std::uint32_t GetData() override;

private:
  std::uint32_t data;
  void ConfigDma();
};

#endif