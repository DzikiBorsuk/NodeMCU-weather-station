// DustSensor.h

#ifndef _DUSTSENSOR_h
#define _DUSTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

void SensorPylu();
float computeDust();
