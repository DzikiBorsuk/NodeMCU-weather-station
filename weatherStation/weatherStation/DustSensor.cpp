//
//
//

#include "DustSensor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define MIN_VOLTAGE     600
#define VREF           3300
#define PIN_LED          D4
#define PIN_ON			   	 D3
#define PIN_ANALOG       A0
#define MAX_ITERS        10

extern PubSubClient client;
extern JsonObject& root;


int ADC_VALUE;
int ITER;
float VOLTAGE;
float DUST;
float AVG_DUST;

float computeDust()
{

	digitalWrite(PIN_LED, HIGH);
	delayMicroseconds(280);
	ADC_VALUE = analogRead(PIN_ANALOG);
	Serial.println(ADC_VALUE);
	digitalWrite(PIN_LED, LOW);

	VOLTAGE = (VREF / 1024.0) * ADC_VALUE;


		return (VOLTAGE - MIN_VOLTAGE) * 0.2;

}

void SensorPylu(JsonObject& root, String& postdata)
{
	char msg[75];
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_ON, OUTPUT);
	digitalWrite(PIN_ON, HIGH);
	digitalWrite(PIN_LED, LOW);
	AVG_DUST = 0;
	ITER = 0;
	while (ITER < MAX_ITERS)
	{
		DUST = computeDust();
			AVG_DUST += DUST;
			ITER++;
			delay(50);

	}
	digitalWrite(PIN_ON, LOW);
	AVG_DUST /= MAX_ITERS;


	snprintf(msg, 75, String(AVG_DUST).c_str());
	root["dust"] = msg;
	delay(50);
	postdata = postdata + "&dust=" + msg;
	delay(50);
	client.publish(dust_topic, msg, true);
	delay(50);
}
