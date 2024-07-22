#ifndef PCF8575_ARTEMIS_h
#define PCF8575_ARTEMIS_h

#include <Wire.h>

class PCF8575_Artemis
{
private:
    /* data */
    TwoWire *_wire;
    uint8_t _address = 0x27;
public:
    PCF8575_Artemis(TwoWire *wireInterface);
    ~PCF8575_Artemis();
    bool begin(uint8_t address);
    uint16_t readPorts();

};

