// 
// 
// 

#include "DustSensor.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#define MIN_VOLTAGE     600 // mv - próg dolnego zakresu napiêcia dla braku py³u
#define VREF           3300 // mv - napiêcie referencyjne komparatora
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
	Serial.println("\t1a");
	digitalWrite(PIN_LED, HIGH);
	Serial.println("\t1b");
	delayMicroseconds(280);
	Serial.println("\t1c");
	ADC_VALUE = analogRead(PIN_ANALOG);
	Serial.println(ADC_VALUE);
	Serial.println("\t1d");
	digitalWrite(PIN_LED, LOW);
	Serial.println("\t1e");
	// Przeliczamy na mV. Calosc mnozymy przez 11, poniewaz w module
	// zastosowano dzielinik napiecia 1k/10k
	VOLTAGE = (VREF / 1024.0) * ADC_VALUE;
	Serial.println("\t1f");
	// Obliczamy zanieczyszczenie jesli zmierzone napiecie ponad prog

	//if (VOLTAGE > MIN_VOLTAGE)
	{
		Serial.println("\t1g");
		return (VOLTAGE - MIN_VOLTAGE) * 0.2;
	}

	//return 0;
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
	Serial.println("0.Przed obliczaniem sredniej");
	while (ITER < MAX_ITERS)
	{
		Serial.println("1");
		DUST = computeDust();
		Serial.println("2");
		// Do sredniej liczmy tylko prawidlowe pomiary
		//if (DUST > 0)
		{
			AVG_DUST += DUST;
			ITER++;
			delay(50);
		}
	}
	digitalWrite(PIN_ON, LOW);
	AVG_DUST /= MAX_ITERS;

	//Serial.print("D = ");
	//Serial.print(AVG_DUST);
	//Serial.println("ug/m3");
	Serial.println("1.Po obliczeniu sredniego pylu");
	snprintf(msg, 75, String(AVG_DUST).c_str());
	root["dust"] = msg;
	Serial.println("2.Po zapisaniu do roota");
	delay(50);
	postdata = postdata + "&dust=" + msg;
	Serial.println("3.Po zapisaniu do postdata");
	delay(50);
	client.publish(dust_topic, msg, true);
	Serial.println("Po opublikowaniu przez MQTT");
	delay(50);
}

