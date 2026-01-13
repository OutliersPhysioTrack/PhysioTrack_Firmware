#ifndef HX711_READER_H
#define HX711_READER_H

#include <Arduino.h>
#include "HX711.h"

// PIN HX711
#define HX711_DT_PIN   32
#define HX711_SCK_PIN  33

// GLOBAL VARIABLE
extern float loadcell_kg;

// FUNCTION
void hx711_init();
void hx711_tare();
void hx711_read(unsigned int nilai_millis);

#endif
