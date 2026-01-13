#include "../header/DHT11Reader.h"

float dht11_temp_value;
float dht11_hum_value;

DHT dht(DHTPIN, DHTTYPE);

// inisialisasi sensor DHT11
void dht11_init()
{
  dht.begin();
}

// membaca suhu lingkungan dengan sensor DHT11
void dht11_temp_read(unsigned int nilai_millis) {
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 500) return;
  prevMillis = nilai_millis;

  float baca_temperature = dht.readTemperature();
  
  if (isnan(baca_temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    dht11_temp_value = -1;
  }

  dht11_temp_value = baca_temperature;
}

// membaca kelembaban lingkungan dengan sensor DHT11
void dht11_hum_read(unsigned int nilai_millis) {
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 500) return;
  prevMillis = nilai_millis;

  float baca_humidity = dht.readHumidity();
  
  if (isnan(baca_humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    dht11_hum_value = -1;
  }

  dht11_hum_value = baca_humidity;
}