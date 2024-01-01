#include <DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
Serial.begin(9600);
dht.begin();
}

void loop()
{
float h = dht.readHumidity();
float t = dht.readTemperature();

float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

Serial.print("DHT11 Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("DHT11 Temperature: ");
Serial.print(t);
Serial.print(" °C ");
Serial.print(f);
Serial.println(" °F\t\n");
delay(1000);
}
