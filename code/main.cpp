#include "rtos.hpp"         // for Rtos
#include "rccregisters.hpp" // for RCC
#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC
#include "usart2registers.hpp" // for Usart2 registers
#include "usart.hpp" // for Usart
#include "measurementtask.hpp"   // for MeasurementTask
#include "pctask.hpp"   // for PCTask
#include "digitalfilter.hpp" // for DigitalFilter
#include "voltage.hpp"       // for Voltage
#include "humidity.hpp" // for Humidity
#include "datastorage.hpp" // for DataStorage
#include "adcdmadataprovider.hpp"   // for ADC
#include "FormatterUsart.hpp"   // for formatter

std::uint32_t SystemCoreClock = 16'000'000U;

extern "C" void TIM2_IRQHandler(void) {}
extern "C" void TIM3_IRQHandler(void) {}
extern "C" void TIM4_IRQHandler(void) {}
extern "C" void USART2_IRQHandler(void) {}
extern "C" void DMA2_Stream0_IRQHandler(void) {}

// ============================================================
// Low Level Initialization
// ============================================================

extern "C" {
  int __low_level_init(void)
  {
    // Switch on internal 16 MHz oscillator
    RCC::CR::HSION::On::Set();
    while (RCC::CR::HSIRDY::NotReady::IsSet()) {}

    // Switch system clock on internal oscillator
    RCC::CFGR::SW::Hsi::Set();
    while (!RCC::CFGR::SWS::Hsi::IsSet()) {}

    // Switch on clock on PortA and PortC
    RCC::AHB1ENRPack<
      RCC::AHB1ENR::GPIOCEN::Enable,
      RCC::AHB1ENR::GPIOAEN::Enable
    >::Set();

    RCC::APB2ENR::SYSCFGEN::Enable::Set();

    // LED outputs
    GPIOA::MODER::MODER5::Output::Set();      // PA5 - LED1
    GPIOC::MODERPack<
      GPIOC::MODER::MODER5::Output,           // PC5 - LED2
      GPIOC::MODER::MODER8::Output,           // PC8 - LED3
      GPIOC::MODER::MODER9::Output            // PC9 - LED4
    >::Set();

    // PA0 as analog input for soil moisture sensor
    GPIOA::MODER::MODER0::Analog::Set();

    // RCC on ADC, DMA and USART2
    RCC::APB2ENR::ADC1EN::Enable::Set();
    RCC::AHB1ENR::DMA2EN::Enable::Set();
    RCC::APB1ENR::USART2EN::Enable::Set();

    return 1;
  }
}

constexpr auto dt = 0.1f;
constexpr auto rc = 5.0f;
constexpr auto offset = 0.0f;
constexpr auto gain = 0.00080566f;  // 3.3V / 4096

AdcDmaDataProvider adc;
DigitalFilter<float, dt, rc> digitalFloatFilter;
Voltage<gain, offset> voltage(static_cast<IDataProvider&>(adc));
DataStorage filteredVoltage;
Humidity calculateHumidity;
Usart usart;                             
FormatterUSART formatter;                 

MeasurementTask measurementTask(digitalFloatFilter, voltage, calculateHumidity, filteredVoltage);
PCTask pctask(filteredVoltage, usart, formatter);  

int main()
{
  USART2::CR1::UE::Enable::Set();
  USART2::CR1::TE::Enable::Set();

  using namespace OsWrapper;

  Rtos::CreateThread(measurementTask, "MeasurementTask", ThreadPriority::priorityMax);
  Rtos::CreateThread(pctask, "PCTask", ThreadPriority::lowest);


  Rtos::Start();

  return 0;
}