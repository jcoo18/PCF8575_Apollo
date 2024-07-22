#include "PCF8575_Artemis.h"
#include "Wire.h"

/**
* Constructor
* @param wireInterface: constructed wire interface
*/
PCF8575_Artemis::PCF8575_Artemis(TwoWire &wireInterface)
{
    _wire = &wireInterface;
}

/**
* Begin
* @param address: i2c address 0x20 to 0x27
*/
bool PCF8575_Artemis::begin(uint8_t address)
{
    _address = address;
     _wire->beginTransmission(_address);
    if (_wire->endTransmission() == 0)
    {
      return true;
    }
    else
    {
        return false;
    }
}

/**
* Function
* @return: 16bit value of all port states
*/
uint16_t PCF8575_Artemis::readPorts()
{
    _wire->beginTransmission(_address);
    if (_wire->endTransmission() == 0)
    {
      _wire->requestFrom(_address,(uint8_t)2);
      //delay(10);
      if(_wire->available())
      {
        uint16_t iInput = _wire->read();// Read a uint16_t
		    iInput |= _wire->read() << 8;// Read a uint16_t
        return iInput;
      }
      return false;
    }
    return false;
}