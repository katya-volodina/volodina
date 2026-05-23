#ifndef IDATAPROVIDER_HPP
#define IDATAPROVIDER_HPP

#include <cstdint>

class IDataProvider
{
public:
  virtual std::uint32_t GetData() = 0;
};

#endif // IDATAPROVIDER_HPP