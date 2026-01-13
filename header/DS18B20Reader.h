#ifndef DS18B20_SENSOR_H
#define DS18B20_SENSOR_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

extern float ds18b20_value;

// KONFIGURASI PIN
// GPIO ESP32 (bisa diganti)
#define DS18B20_PIN 4   

// FUNCTION
void ds18b20_init();
void ds18b20_read(unsigned int nilai_millis);

#endif