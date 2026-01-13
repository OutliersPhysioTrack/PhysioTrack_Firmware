#ifndef DHT11_READER_H
#define DHT11_READER_H

#include <DHT.h>

// KONFIGURASI
#define DHTPIN   5
#define DHTTYPE  DHT11

// VARIABLE GLOBAL
extern float dht11_temp_value;
extern float dht11_hum_value;

// FUNCTION
void dht11_init();
void dht11_hum_read(unsigned int nilai_millis);
void dht11_temp_read(unsigned int nilai_millis);

#endif
