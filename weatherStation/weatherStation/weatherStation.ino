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
#include <ESP8266HTTPClient.h>

#define sensor_topic "esp8266/weatherS"
const char* host = "127.0.0.1"; //??
Adafruit_BME680 bme;	//sensorBME
WiFiClient espClient;			//wifirifi
PubSubClient client(espClient);



void wifiSetup();
// the setup function runs once when you press reset or power the board
void setup() {
	unsigned long endTime = 0;
	double toCalculateTenMins;
	Serial.begin(115200);
	wifiSetup();	// WiFi initialization
	setMqttConnection(); //starting mqtt

		if (!client.connected()) {
			MQTTReconnect(); //We are looking if we are connected to the mqtt, if not:reconnect
		}
		client.loop(); //client.loop() should be called regularly to allow the client to process incoming messages to send publish data and makes a refresh of the connection.
		sendingByMqtt();
		endTime = micros(); //We are checking the time since the start of the program , unsigned long
		toCalculateTenMins = static_cast<double>(endTime); //we are casting  to  double to make it enter deepsleep
		ESP.deepSleep(6E8-toCalculateTenMins, WAKE_RF_DEFAULT); //deepsleep for every 10min
		//ESP.deepSleep(30E6, WAKE_RF_DEFAULT);




}

void loop()
{}
void sendingByMqtt()
{
	StaticJsonBuffer<200> jsonBuffer;		//setting json buffer (rozmiar 200?)
	JsonObject& root = jsonBuffer.createObject(); //creating  json object
	//root["Sensor"] = "ESP8266";
	SensorBME680(root);			// bme680(4 sensors) call, we are passing  jsonobject as an argument because we want the response also in json
	char JSONmessageBuffer[200];
	root.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer)); //rewriting from root to jsonmessagebuffer
	Serial.println(JSONmessageBuffer);
	client.publish(sensor_topic, JSONmessageBuffer, true); //we are looking if it was send to mqtt to sensor_topic (esp8266/weatherS), if it was send then the loop ends
}
void setMqttConnection()
{
	const char* mqtt_server = "cpsiot.cs.uni-kl.de"; //name of MQTT server
	client.setServer(mqtt_server, 1883);	//setting of  server properties, port 1883 is default port of brokera
}
void wifiSetup()
{
	const char* ssid = "CPSWirelessNetwork";
	const char* password = "Wifi&49CPS";
	Serial.println("Booting");
	Serial.println("Connecting to WiFI");
	WiFi.forceSleepWake(); //required for deep sleepa
	Serial.println("Przed podaniem hasla");
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

void HTTPtoWebsite(String postdata)
{
	HTTPClient http;
	http.begin("http://185.243.55.40/postdemo.php");
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	int httpCode = http.POST(postdata);
	String payload = http.getString();
	Serial.println(httpCode);
	Serial.println(payload);
	http.end();
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
		bme.setTemperatureOversampling(BME680_OS_8X); //Setter for Temperature oversampling.
		bme.setHumidityOversampling(BME680_OS_2X);
		bme.setPressureOversampling(BME680_OS_4X);
		bme.setIIRFilterSize(BME680_FILTER_SIZE_3); //removes short-term fluctuations
		bme.setGasHeater(320, 150); // 320*C for 150 ms
		if (!bme.performReading()) {	//robimy odczyty z BME680
			Serial.println("Failed to perform reading :(");
			return;
		}

		String postdata;
		temperatureMeasure(root,postdata);
		delay(50);
		pressureMeasure(root,postdata);
		delay(50);
		altitudeMeasure(root,postdata);
		delay(50);
		humidityMeasure(root,postdata);
		delay(50);
		gasMeasure(root,postdata);
		delay(50);

		HTTPtoWebsite(postdata);



}
