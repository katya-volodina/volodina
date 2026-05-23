#ifndef IFILTER_HPP
#define IFILTER_HPP

template<typename T>
class IFilter
{
public:
  virtual T FilterValue(T value) = 0;
  virtual ~IFilter() = default;
};

#endif // IFILTER_HPP