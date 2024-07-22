#include <Wire.h>
#include <PCF8575_Artemis.h>
//#include "PCF8575_Artemis.h"

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

PCF8575_Artemis pcf(qwiic);

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

void qwiicPowerOn()
{
  pinMode(PIN_QWIIC_POWER, OUTPUT);
#if(HARDWARE_VERSION_MAJOR == 0)
  digitalWrite(PIN_QWIIC_POWER, LOW);
#else
  digitalWrite(PIN_QWIIC_POWER, HIGH);
#endif
}
void qwiicPowerOff()
{
  pinMode(PIN_QWIIC_POWER, OUTPUT);
#if(HARDWARE_VERSION_MAJOR == 0)
  digitalWrite(PIN_QWIIC_POWER, HIGH);
#else
  digitalWrite(PIN_QWIIC_POWER, LOW);
#endif
}

void setQwiicPullups(uint32_t qwiicBusPullUps)
{
  //Change SCL and SDA pull-ups manually using pin_config
  am_hal_gpio_pincfg_t sclPinCfg = g_AM_BSP_GPIO_IOM1_SCL;
  am_hal_gpio_pincfg_t sdaPinCfg = g_AM_BSP_GPIO_IOM1_SDA;

  if (qwiicBusPullUps == 0)
  {
    sclPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_NONE; // No pull-ups
    sdaPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_NONE;
  }
  else if (qwiicBusPullUps == 1)
  {
    sclPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_1_5K; // Use 1K5 pull-ups
    sdaPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_1_5K;
  }
  else if (qwiicBusPullUps == 6)
  {
    sclPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_6K; // Use 6K pull-ups
    sdaPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_6K;
  }
  else if (qwiicBusPullUps == 12)
  {
    sclPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_12K; // Use 12K pull-ups
    sdaPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_12K;
  }
  else
  {
    sclPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_24K; // Use 24K pull-ups
    sdaPinCfg.ePullup = AM_HAL_GPIO_PIN_PULLUP_24K;
  }

  pin_config(PinName(PIN_QWIIC_SCL), sclPinCfg);
  pin_config(PinName(PIN_QWIIC_SDA), sdaPinCfg);
}
