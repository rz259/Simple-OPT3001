/****************************************************************************/
/*                                                                          */
/*                                                                          */
/* Author   : Rudolf Ziegaus                                                */
/*                                                                          */
/* Date     : 2020-12-22                                                    */
/*                                                                          */
/* Version  : 1.0                                                           */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


#include "OPT3001.h"
#include "Wire.h"

const int OPT3001_ADDRESS = 0x44;

OPT3001 lightSensor(OPT3001_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  int deviceId, manufacturerId, configBytes;

  manufacturerId = lightSensor.getManufacturerId();
  Serial.print("Manufacturer ID : ");
  Serial.println(manufacturerId, HEX);
  deviceId = lightSensor.getDeviceId();
  Serial.print("Device ID : ");
  Serial.println(deviceId, HEX);
}

void loop() 
{
   double lux;

   lux = lightSensor.getLux();
   Serial.println("Lux: " + String(lux));
   delay(5000);
}
