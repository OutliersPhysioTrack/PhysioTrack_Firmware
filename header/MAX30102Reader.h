#ifndef MAX30102_READER_H
#define MAX30102_READER_H

#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

// KONFIGURASI
#define BUFFER_LENGTH 100

// VARIABLE GLOBAL
extern MAX30105 particleSensor;

extern uint32_t irBuffer[BUFFER_LENGTH];
extern uint32_t redBuffer[BUFFER_LENGTH];

// OUTPUT VARIABLE
extern int32_t spo2_value;
extern int32_t heartRate_value;

// VALIDITY FLAG
extern int8_t  validSPO2;
extern int8_t  validHeartRate;

// FUNCTION
void max30102_init();
void max30102_read_first();
void max30102_read(unsigned int nilai_millis);

#endif
