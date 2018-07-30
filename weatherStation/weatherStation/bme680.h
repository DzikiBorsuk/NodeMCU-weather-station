// bme680.h

#ifndef _BME680_h
#define _BME680_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

void SensorBME680();
void MQTTReconnect();