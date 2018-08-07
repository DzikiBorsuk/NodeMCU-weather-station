// bme680.h

#ifndef _BME680_h
#define _BME680_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoJson.h>
#endif
#define SEALEVELPRESSURE_HPA (1013.25)
#define temperature_topic "esp8266/temperature"
#define humidity_topic "esp8266/humidity"
#define gas_topic "esp8266/gas"
#define pressure_topic "esp8266/pressure"
#define altitude_topic "esp8266/altitude"

void MQTTReconnect();
void temperatureMeasure(JsonObject& root, String& postdata);
void humidityMeasure(JsonObject& root,String& postdata);
void gasMeasure(JsonObject& root, String& postdata);
void pressureMeasure(JsonObject& root, String& postdata);
void altitudeMeasure(JsonObject& root, String& postdata);