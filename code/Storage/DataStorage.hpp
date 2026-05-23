#ifndef DATASTORAGE_HPP
#define DATASTORAGE_HPP

#include "idataproviders.hpp" //for IDataProviders
#include "idatasetter.hpp" //for IDataSetter

class DataStorage: public IDataProviders, public IDataSetter
{
public:
  DataStorage();
  float GetData() const override;
  float SetData(float value) override;
private:
  float mValue;
};

#endif // DATASTORAGE_HPP