
#include "bme680.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
Adafruit_BME680 bme1; // I2C
// 
// 
// 
/*


#define temperature_topic "esp8266/temperature"




void SensorBME680() {
	Serial.begin(115200);
	while (!Serial);
	Serial.println(F("BME680 test"));

	if (!bme.begin()) {
		Serial.println("Could not find a valid BME680 sensor, check wiring!");
		while (1);
	}

	// Set up oversampling and filter initialization
	bme.setTemperatureOversampling(BME680_OS_8X);
	bme.setHumidityOversampling(BME680_OS_2X);
	bme.setPressureOversampling(BME680_OS_4X);
	bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
	bme.setGasHeater(320, 150); // 320*C for 150 ms



		if (!bme.performReading()) {
			Serial.println("Failed to perform reading :(");
			return;
		}
		Serial.print("Temperature = ");
		Serial.print(bme.temperature);
		Serial.println(" *C");

		Serial.print("Pressure = ");
		Serial.print(bme.pressure / 100.0);
		Serial.println(" hPa");

		Serial.print("Humidity = ");
		Serial.print(bme.humidity);
		Serial.println(" %");

		Serial.print("Gas = ");
		Serial.print(bme.gas_resistance / 1000.0);
		Serial.println(" KOhms");

		Serial.print("Approx. Altitude = ");
		Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
		Serial.println(" m");

		Serial.println();
		delay(2000);
	
}

*/

extern Adafruit_BME680 bme;
extern PubSubClient client;
extern JsonObject& root;

void temperatureMeasure(JsonObject& root)
{
	char msg[50];
	float temp = bme.temperature;
	Serial.print("Temperature = ");
	Serial.print(String(temp).c_str());
	Serial.println(" *C");
	snprintf(msg, 75, String(temp).c_str());
	root["temperature"] = msg;
	//client.publish(temperature_topic, msg, true);
}
void humidityMeasure(JsonObject& root)
{
	char msg[50];
	float temp = bme.humidity;
	Serial.print("Humidity = ");
	Serial.print(String(temp).c_str());
	Serial.println(" %");
	snprintf(msg, 75, String(temp).c_str());
	root["humidity"] = msg;
	//client.publish(humidity_topic, msg, true);
}
void gasMeasure(JsonObject& root)
{
	char msg[50];
	float temp = bme.gas_resistance/1000.0;
	Serial.print("Gas = ");
	Serial.print(String(temp).c_str());
	Serial.println(" KOhms");
	snprintf(msg, 75, String(temp).c_str());
	root["gas"] = msg;
	//client.publish(gas_topic, msg, true);
}
void pressureMeasure(JsonObject& root)
{
	char msg[50];
	float temp = bme.pressure/100.0;
	Serial.print("Pressure = ");
	Serial.print(String(temp).c_str());
	Serial.println(" hPa");
	snprintf(msg, 75, String(temp).c_str());
	root["pressure"] = msg;
	//client.publish(pressure_topic, msg, true);
}
void altitudeMeasure(JsonObject& root)
{
	char msg[50];
	float temp = bme.readAltitude(SEALEVELPRESSURE_HPA);
	Serial.print("Approx. Altitude = ");
	Serial.print(String(temp).c_str());
	Serial.println(" m");
	snprintf(msg, 75, String(temp).c_str());
	root["altitude"] = msg;
	client.publish(altitude_topic, msg, true);
	//Serial.println("Opublikowalem wysokosc");
}