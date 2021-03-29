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



#include <Wire.h>

#include "OPT3001.h"

#define RESULT_REGISTER             0x00
#define CONFIG_REGISTER             0x01
#define	LOW_LIMIT_REGISTER	        0x02
#define	HIGH_LIMIT_REGISTER 	      0x03
#define	MANUFACTURER_ID_REGISTER    0x7E
#define	DEVICE_ID_REGISTER          0x7F



/*
 default configuration bytes:
 - automatic full scale mode
 - conversion time 800 ms
 - continuous conversion mode
*/ 

uint8_t defaultConfigBytes[] = {0xCE, 0x10};  // 1100 1110 0001 0000 binary



OPT3001::OPT3001(int address, uint8_t configBytes[], int size)
{
	this->address = address;
	Wire.begin();
	if (configBytes != NULL && size > 0)
	{
	  configure(configBytes, size);
	}
	else
	{
	  configure();
	}
}


// get the current brightness

double OPT3001::getLux()
{
	uint16_t data;
	double   lux;
	
	data = readRegister(RESULT_REGISTER);       // read result from result register
  lux = convertToLux(data);								    // and convert to lux
	return lux;
}

// configure with default config bytes

void OPT3001::configure()
{
	configure(defaultConfigBytes, sizeof(defaultConfigBytes));  
}

// configure with user defined config bytes

void OPT3001::configure(uint8_t configBytes[], int size)
{
  Wire.beginTransmission(getAddress());
  Wire.write(CONFIG_REGISTER);
  Wire.write(configBytes, size);
  Wire.endTransmission();
}

// retrieve the manufacturer ID 
// always 0x5449 ("TI")

uint16_t OPT3001::getManufacturerId()
{
	return readRegister(MANUFACTURER_ID_REGISTER);
}

// retrieve the device  ID 
// always 0x3001 

uint16_t OPT3001::getDeviceId()
{
	return readRegister(DEVICE_ID_REGISTER);
}

// retrieve the current configuration  

uint16_t OPT3001::getConfigBytes()
{
	return readRegister(CONFIG_REGISTER);
}


// convert the retrieved binary value to lux
double OPT3001::convertToLux(uint16_t data)
{
  uint16_t exponent, mantissa;
  double value;

  mantissa = data & 0x0FFF;              // mantissa is stored in bit  0 to 11
  exponent = (data & 0xF000) >> 12;      // exponent is stored in bit 12 to 15
  value = mantissa * (0.01 * pow(2, exponent)); // calculate lux from formula in datasheet pg. 21
  return value;
}


int OPT3001::getAddress()
{
	return address;
}

uint16_t OPT3001::readRegister(int registerId)
{
	uint16_t data = 0;
	uint8_t  buffer[2];
	
	Wire.beginTransmission(getAddress());    
  Wire.write(registerId);									 // first transmit register to read
  Wire.endTransmission();                  
  Wire.requestFrom(getAddress(), 2);       // now request and read 2 bytes  
  while (Wire.available())
  {
    Wire.readBytes(buffer, 2);
		data = 256 * buffer[0] + buffer[1];  // result is in BigEndian so we have to convert it so LittleEndian
  }
  return data;
}
