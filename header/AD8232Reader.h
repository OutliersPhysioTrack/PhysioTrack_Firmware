#ifndef SENSOR_ADC_H
#define SENSOR_ADC_H

#include <Arduino.h>

extern int ecg_value;

// KONFIGURASI PIN
// GPIO ADC ESP32 (32–39)
#define SENSOR_PIN 34   

// FUNCTION
void ecg_init();
void  ecg_read(unsigned int nilai_millis);

#endif
