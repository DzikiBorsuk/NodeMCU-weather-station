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
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <ArduinoJson.h>


#define PIN_LED          D6
#define sensor_topic "esp8266/weatherS"
#define dust_topic "esp8266/dust"
Adafruit_BME680 bme;
unsigned long endTime = 0;
double toCalculateTenMins;
WiFiClient espClient;
PubSubClient client(espClient);
void wifiSetup();


// the setup function runs once when you press reset or power the board
void setup() {
	
	//beginTime = millis();
	Serial.begin(115200);
	//pinMode(PIN_LED, OUTPUT);
	const char* mqtt_server = "cpsiot.cs.uni-kl.de";
	wifiSetup();
	client.setServer(mqtt_server, 1883);
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
		if (!client.connected()) {
			MQTTReconnect();
		}
		client.loop();
		root["Sensor"] = "ESP8266";
		SensorBME680(root);
		SensorPylu(root);
		Serial.println(root.measureLength() + 1);
		//root.prettyPrintTo(Serial);
		char JSONmessageBuffer[200];
		root.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
		Serial.println(JSONmessageBuffer);
		
		while (!client.publish(sensor_topic, JSONmessageBuffer, true))
		{
			delay(20);
		}
		char JSONmessageBuffer1[150];
			/*Serial.println("udalo sie wyslac poprzez MQTT");
		else
			Serial.println("I couldnt send over MQTT");*/
		endTime = micros();
		toCalculateTenMins = static_cast<double>(endTime);
		//Serial.println(toCalculateTenMins);
		//Serial.println("INFO:Closing MQTT connection");
		//client.disconnect();
		//Serial.println("Info:Closing WIFI connection");
		//WiFi.disconnect();
		//int i = 0;
		//while (client.connected()||(WiFi.status()==WL_CONNECTED))
		//{
		//	Serial.println(i++);
		//	delay(10);
		//}
		//ESP.deepSleep(60E6-toCalculateTenMins, WAKE_RF_DEFAULT);
		ESP.deepSleep(5e6, WAKE_RF_DEFAULT);
		



}



// the loop function runs over and over again until power down or reset
void loop()
{
	/*int x;
	
	digitalWrite(PIN_LED, HIGH);
	delay(50);
	x = analogRead(A0);
	delay(1);
	digitalWrite(PIN_LED, LOW);
	Serial.println(x);
	delay(500);*/
	


}

void wifiSetup()
{
	const char* ssid = "CPSWirelessNetwork";
	const char* password = "Wifi&49CPS";
	Serial.println("Booting");
	Serial.println("Connecting to WiFI");
	WiFi.forceSleepWake();
	Serial.println("Przed podaniem hasla");

	
//>>>>>>> parent of 0f4c11f... usuniecie paru niepotrzebnych linijek, dodanie DeepSleepu(ale nie dziala jezscze perfekcyjnie)
	WiFi.begin(ssid, password);
	Serial.println("Po podaniu hasla");
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}


	
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


void SensorBME680(JsonObject& root)
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
		//temperatureMeasure1(root);
		temperatureMeasure(root);
		pressureMeasure(root);
		altitudeMeasure(root);
		humidityMeasure(root);
		gasMeasure(root);
		
		
		
}
void temperatureMeasure1(JsonObject& root)
{
	char msg[50];
	float temp = bme.temperature;
	Serial.print("Temperature = ");
	Serial.print(String(temp).c_str());
	Serial.println(" *C");
	snprintf(msg, 75, String(temp).c_str());
	
	root["temperature"] = msg;
	Serial.println(msg);
	client.publish(temperature_topic, msg, true);
}