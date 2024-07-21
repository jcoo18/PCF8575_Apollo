#include <Wire.h>
#include "PCF8575_Apollo.h"

const byte PIN_QWIIC_SCL = 8;
const byte PIN_QWIIC_SDA = 9;
TwoWire qwiic(PIN_QWIIC_SDA, PIN_QWIIC_SCL); // Will use pads 8/9

const byte PIN_QWIIC_POWER = 18;

// Define the pin functions
// Depends on hardware version. This can be found as a marking on the PCB.
// x04 was the SparkX 'black' version.
// v10 was the first red version.
#define HARDWARE_VERSION_MAJOR 1
#define HARDWARE_VERSION_MINOR 0

PCF8575_Apollo pcf(qwiic);

void setup()
{
    Serial.begin(115200);
    Serial.println("Scanning...");

    qwiicPowerOn();

    qwiic.begin();
    qwiic.setClock(100000);

    setQwiicPullups(1); // Set pullups to 1K5

    bool retval = pcf.begin(0x27);
    Serial.print("PCF8575 return value: ");
    Serial.println(retval);
}
void loop()
{
    uint16_t ports = pcf.readPorts();
    Serial.print("Port Read: \n");
    Serial.println(ports, DEC);
    Serial.println(ports, HEX);
    Serial.println(ports, BIN);

    delay(1000);
}