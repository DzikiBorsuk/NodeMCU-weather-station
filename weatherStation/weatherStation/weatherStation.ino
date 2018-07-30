/*
 Name:		weatherStation.ino
 Created:	21.06.2018 11:52:42
 Author:	Piotr Meller
*/


#include <PubSubClient.h>
#include "DustSensor.h"
#include "bme680.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define PIN_LED          D6

Adafruit_BME680 bme;

WiFiClient espClient;
PubSubClient client(espClient);
void wifiSetup();


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	//pinMode(PIN_LED, OUTPUT);
	const char* mqtt_server = "cpsiot.cs.uni-kl.de";
	wifiSetup();
	client.setServer(mqtt_server, 1883);
	
		if (!client.connected()) {
			MQTTReconnect();
		}
		client.loop();
		SensorBME680();
		ESP.deepSleep(30E6);
	//SensorPylu();



}



// the loop function runs over and over again until power down or reset
void loop()
{
}

void wifiSetup()
{
	const char* ssid = "CPSWirelessNetwork";
	const char* password = "Wifi&49CPS";
	Serial.println("Booting");
	Serial.println("Connecting to WiFI");
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}

	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}

void MQTTReconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		// If you do not want to use a username and password, change next line to
		// if (client.connect("ESP8266Client")) {
		if (client.connect("ESP8266Client")) {
			Serial.println("connected");
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}


void SensorBME680()
{
	while (!Serial);
	Serial.println(F("BME680 test"));

	if (!bme.begin()) {
		Serial.println("Could not find a valid BME680 sensor, check wiring!");
		while (1);
	}
		//Set up oversampling and filter initialization
		bme.setTemperatureOversampling(BME680_OS_8X);
		bme.setHumidityOversampling(BME680_OS_2X);
		bme.setPressureOversampling(BME680_OS_4X);
		bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
		bme.setGasHeater(320, 150); // 320*C for 150 ms
		if (!bme.performReading()) {
			Serial.println("Failed to perform reading :(");
			return;
		}
		
		temperatureMeasure();
		humidityMeasure();
		Serial.println("Sprawdzenie w miedzyczasie");
		gasMeasure();
		pressureMeasure();
		altitudeMeasure();
}
