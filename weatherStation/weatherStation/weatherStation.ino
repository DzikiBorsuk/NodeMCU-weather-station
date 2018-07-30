/*
 Name:		weatherStation.ino
 Created:	21.06.2018 11:52:42
 Author:	Piotr Meller
*/


#include <PubSubClient.h>
#include "DustSensor.h"
//#include "bme680.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define PIN_LED          D6
#define temperature_topic "esp8266/temperature"
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
	while (true)
	{
		if (!client.connected()) {
			MQTTReconnect();
		}
		client.loop();
		temp();
	}
	//SensorPylu();



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
	
	ArduinoOTA.handle();


}

void wifiSetup()
{
	const char* ssid = "CPSWirelessNetwork";
	const char* password = "Wifi&49CPS";
	Serial.println("Booting");
	Serial.println("Connecting to WiFI");
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}

	// Port defaults to 8266
	// ArduinoOTA.setPort(8266);

	// Hostname defaults to esp8266-[ChipID]
	// ArduinoOTA.setHostname("myesp8266");

	// No authentication by default
	// ArduinoOTA.setPassword("admin");

	// Password can be set with it's md5 value as well
	// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

	ArduinoOTA.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Start updating " + type);
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
	});
	ArduinoOTA.begin();
	Serial.println("Ready");
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

void temp()
{
	char msg[50];
	while (!Serial);
	Serial.println(F("BME680 test"));

	if (!bme.begin()) {
		Serial.println("Could not find a valid BME680 sensor, check wiring!");
		while (1);
	}
	bme.setTemperatureOversampling(BME680_OS_8X);
	if (!bme.performReading()) {
		Serial.println("Failed to perform reading :(");
		return;
	}
	Serial.print("Temperature = ");
	float temp = bme.temperature;
	Serial.print(String(temp).c_str());
	Serial.println(" *C");
	snprintf(msg, 75, String(temp).c_str());
	client.publish(temperature_topic,msg,true);
}