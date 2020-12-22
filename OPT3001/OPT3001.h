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


#ifndef OPT3001_H
#define OPT3001_H

#include <Arduino.h>


class OPT3001
{
  public:
	  OPT3001(int address, uint8_t configBytes[] = NULL, int size = 0);
		void configure();
    void configure(uint8_t configBytes[], int size);
		
		double getLux();
		uint16_t getManufacturerId();
		uint16_t getDeviceId();
		uint16_t getConfigBytes();
		
		
		
		
	private:
	  int    address;
		int    getAddress();
		double convertToLux(uint16_t data);
		uint16_t readRegister(int registerId);
};
#endif
