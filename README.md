# Simple-OPT3001
Simple C++ library for Arduino to retrieve the brightness with the OPT3001 sensor from TI

This library allows for a simple usage of the OPT3001 sensor from TI.
It does not support the adavanced features (such  as the interrupt mechanism or the low limit and high limit register), however is very easy to use.
The sensor is automatically setup with a default confuguration with the following features

 - automatic full scale mode
 - conversion time 800 ms
 - continuous conversion mode

If you wish you can change the configuration by using the method configure and the appropriate configuration values (see datasheet of the sensor).

The library also supports methods to get the manufacturer ID and the device ID. However these are constant values.
The manufacturer ID always reads 0x5449 ("TI") and the device ID always reads 0x3001, so these values are of limited use. Thus you cannot distingish 
individual sensors based on their IDs.


Included is a very simple sample sketch for Arduino which shows how to read the current brightness from the sensor.

The sketch has been tested with an NodeMCU-32 board.
