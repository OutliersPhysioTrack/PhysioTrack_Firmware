#include "../header/DS18B20Reader.h"

float ds18b20_value;

// OBJECT GLOBAL
OneWire oneWire_DS18B20(DS18B20_PIN);
DallasTemperature DS18B20(&oneWire_DS18B20);

// INIT SENSOR
void ds18b20_init()
{
  DS18B20.begin();
}

// BACA TEMPERATUR
void ds18b20_read(unsigned int nilai_millis)
{
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 2000) return;
  prevMillis = nilai_millis;

  DS18B20.requestTemperatures();

  // delay kecil untuk konversi (default 12-bit)
  delay(100);

  float temperatureC = DS18B20.getTempCByIndex(0);

if (temperatureC == DEVICE_DISCONNECTED_C) {
  ds18b20_value = -100;
} else {
  ds18b20_value = temperatureC;
}
ds18b20_value = temperatureC;
}
