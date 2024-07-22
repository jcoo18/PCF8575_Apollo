#ifndef PCF8575_ARTEMIS_H
#define PCF8575_ARTEMIS_H
#endif

#include <Wire.h>

class PCF8575_Artemis
{
private:
    /* data */
    TwoWire *_wire;
    uint8_t _address;
public:
    PCF8575_Artemis(TwoWire &wireInterface);
    //~PCF8575_Artemis();
    bool begin(uint8_t address = 0x27);
    uint16_t readPorts();

};

