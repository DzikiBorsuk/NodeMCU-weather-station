// 
// 
// 

#include "DustSensor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define MIN_VOLTAGE     600 // mv - próg dolnego zakresu napiêcia dla braku py³u
#define VREF           5000 // mv - napiêcie referencyjne komparatora
#define PIN_LED          D4 // numer pinu ILED
#define PIN_ON			 D3	//uruchomienie sensora
#define PIN_ANALOG       A0 // numer pinu AOUT
#define MAX_ITERS        10 // liczba pomiarow do sredniej

extern PubSubClient client;
extern JsonObject& root;

int ADC_VALUE; // odczytana wartosc A0
int ITER; // numer pomiaru
float VOLTAGE; // wartosc napiecia
float DUST; // wynik
float AVG_DUST; // sredni wynik

float computeDust()
{
	// Blyskamy IR, czekamy 280ms, odczytujemy napiecie ADC
	digitalWrite(PIN_LED, HIGH);
	delayMicroseconds(280);
	ADC_VALUE = analogRead(PIN_ANALOG);
	digitalWrite(PIN_LED, LOW);

	// Przeliczamy na mV. Calosc mnozymy przez 11, poniewaz w module
	// zastosowano dzielinik napiecia 1k/10k
	VOLTAGE = (VREF / 1024.0) * ADC_VALUE * 11;

	// Obliczamy zanieczyszczenie jesli zmierzone napiecie ponad prog

	if (VOLTAGE > MIN_VOLTAGE)
	{
		return (VOLTAGE - MIN_VOLTAGE) * 0.2;
	}

	return 0;
}

void SensorPylu(JsonObject& root)//, String& postdata)
{
	char msg[50];
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_ON, OUTPUT);
	digitalWrite(PIN_ON, HIGH);
	digitalWrite(PIN_LED, LOW);
	AVG_DUST = 0;
	ITER = 0;

	while (ITER < MAX_ITERS)
	{
		DUST = computeDust();
		// Do sredniej liczmy tylko prawidlowe pomiary
		if (DUST > 0)
		{
			AVG_DUST += DUST;
			ITER++;
			delay(50);
		}
	}
	digitalWrite(PIN_ON, LOW);
	AVG_DUST /= MAX_ITERS;

	Serial.print("D = ");
	Serial.print(AVG_DUST);
	Serial.println("ug/m3");
	snprintf(msg, 75, String(AVG_DUST).c_str());
	root["dust"] = msg;
	//postdata = postdata + "&dust=" + msg;
	client.publish(dust_topic, msg, true);
}

