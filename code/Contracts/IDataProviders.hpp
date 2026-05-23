#ifndef IDATAPROVIDERS_HPP
#define IDATAPROVIDERS_HPP

class IDataProviders
{
public:
  virtual float GetData() const = 0;
  virtual ~IDataProviders() = default;
};

#endif // IDATAPROVIDERS_HPP