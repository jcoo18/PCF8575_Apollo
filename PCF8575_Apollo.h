#ifndef PCF8575_APOLLO_h
#define PCF8575_APOLLO_h

#include <Wire.h>

class PCF8575_Apollo
{
private:
    /* data */
    TwoWire *_wire;
    uint8_t _address = 0x27;
public:
    PCF8575_Apollo(TwoWire *wireInterface);
    ~PCF8575_Apollo();
    bool begin(uint8_t address);
    uint16_t readPorts();

};

