
#include "bme680.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
Adafruit_BME680 bme1; // I2C
extern Adafruit_BME680 bme;
extern PubSubClient client;
extern JsonObject& root;

void temperatureMeasure(JsonObject& root, String& postdata)
{
	char msg[50];
	float temp = bme.temperature;
	Serial.print("Temperature = ");
	Serial.print(String(temp).c_str());
	Serial.println(" *C");
	snprintf(msg, 75, String(temp).c_str());
	root["temperature"] = msg;
	postdata = postdata + "temperature=" + msg;
	client.publish(temperature_topic, msg, true);
}
void humidityMeasure(JsonObject& root, String& postdata)
{
	char msg[50];
	float temp = bme.humidity;
	Serial.print("Humidity = ");
	Serial.print(String(temp).c_str());
	Serial.println(" %");
	snprintf(msg, 75, String(temp).c_str());
	root["humidity"] = msg;
	postdata = postdata + "&humidity=" + msg;
	client.publish(humidity_topic, msg, true);
}
void gasMeasure(JsonObject& root, String& postdata)
{
	char msg[50];
	float temp = bme.gas_resistance/1000.0;
	Serial.print("Gas = ");
	Serial.print(String(temp).c_str());
	Serial.println(" KOhms");
	snprintf(msg, 75, String(temp).c_str());
	root["gas"] = msg;
	postdata = postdata + "&gas=" + msg;
	client.publish(gas_topic, msg, true);
}
void pressureMeasure(JsonObject& root, String& postdata)
{
	char msg[50];
	float temp = bme.pressure/100.0;
	Serial.print("Pressure = ");
	Serial.print(String(temp).c_str());
	Serial.println(" hPa");
	snprintf(msg, 75, String(temp).c_str());
	root["pressure"] = msg;
	postdata = postdata + "&pressure=" + msg;
	client.publish(pressure_topic, msg, true);
}
void altitudeMeasure(JsonObject& root, String& postdata)
{
	char msg[50];
	float temp = bme.readAltitude(SEALEVELPRESSURE_HPA);
	Serial.print("Approx. Altitude = ");
	Serial.print(String(temp).c_str());
	Serial.println(" m");
	snprintf(msg, 75, String(temp).c_str());
	root["altitude"] = msg;
	postdata = postdata + "&altitude=" + msg;
	client.publish(altitude_topic, msg, true);
	//Serial.println("Opublikowalem wysokosc");
}