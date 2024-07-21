#ifndef PCF8575_Atremis_h
#define PCF8575_Atremis_h

#include <Wire.h>

class PCF8575_Atremis
{
private:
    /* data */
    TwoWire *_wire;
    uint8_t _address = 0x27;
public:
    PCF8575_Atremis(TwoWire *wireInterface);
    ~PCF8575_Atremis();
    bool begin(uint8_t address);
    uint16_t readPorts();

};

