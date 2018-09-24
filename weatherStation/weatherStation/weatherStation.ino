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
PubSubClient client(espClient); //do mqtt 



void wifiSetup();
// the setup function runs once when you press reset or power the board
void setup() {
	unsigned long endTime = 0;
	double toCalculateTenMins;
	Serial.begin(115200);
	wifiSetup();	//inicjalizacja WiFi	
	setMqttConnection(); //starting mqtt
	
		if (!client.connected()) {
			MQTTReconnect(); //patrzymy czy jestesmy polaczeni do mqtt, jesli nie to reconnect
		}
		client.loop(); //client.loop() should be called regularly to allow the client to process incoming messages to send publish data and makes a refresh of the connection.
		sendingByMqtt();
		endTime = micros(); //obliczamy czas od poczatku wlaczenia mikrokontrolera, unsigned long
		toCalculateTenMins = static_cast<double>(endTime); //rzutujemy to na double, zeby w deepsleepa weszlo
		ESP.deepSleep(6E8-toCalculateTenMins, WAKE_RF_DEFAULT); //deepsleep co 10min
		//ESP.deepSleep(30E6, WAKE_RF_DEFAULT);
		



}

void loop()
{}
void sendingByMqtt()
{
	StaticJsonBuffer<200> jsonBuffer;		//ustawienie buforu json (rozmiar 200?)	
	JsonObject& root = jsonBuffer.createObject(); //stworzenie obiektu json
	//root["Sensor"] = "ESP8266"; //do Json, pod sensor bedzie esp8266
	SensorBME680(root);			//wywolanie bme680(5 czujnikow), jako argument przekazujemy jsonobject, zeby zwrocic rowniez w json odpowiedz
	char JSONmessageBuffer[200]; //tablica o rozmiarze 200 char
	root.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer)); //przepisanie z roota do tablicy jsonmessagebuffer
	Serial.println(JSONmessageBuffer); //wypisanie w porcie szeregowym w JSON
	client.publish(sensor_topic, JSONmessageBuffer, true); //patrzymy czy wyslal do mqtt pod topic sensor_topic (esp8266/weatherS), jak wyslal to wtedy petla sie konczy
	delay(300); //musi!
}
void setMqttConnection()
{
	const char* mqtt_server = "cpsiot.cs.uni-kl.de"; //nazwa serwera MQTT
	client.setServer(mqtt_server, 1883);	//ustawienie szczegolow serwera, port 1883 to nominalny port brokera
}
void wifiSetup()
{
	const char* ssid = "CPSWirelessNetwork";
	const char* password = "Wifi&49CPS";
	Serial.println("Booting");
	Serial.println("Connecting to WiFI");
	WiFi.forceSleepWake(); //potrzbene do deep sleepa, funkcja bool
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
		bme.setIIRFilterSize(BME680_FILTER_SIZE_3); //removes short-term fluctuations. nie jest potrzebny dla wilgotnosci i gazu
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
		//SensorPylu(root, postdata);
		//delay(50);
		HTTPtoWebsite(postdata);
		
		
		
}