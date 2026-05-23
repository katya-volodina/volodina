#include "datastorage.hpp"   // for DataStorage

DataStorage :: DataStorage()
{
}

float DataStorage :: GetData() const
{
  return mValue;
}

float DataStorage :: SetData(float value)
{
  return mValue = value;
}