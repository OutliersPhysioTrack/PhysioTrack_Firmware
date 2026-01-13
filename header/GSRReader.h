#ifndef GSR_READER_H
#define GSR_READER_H

#include <Arduino.h>

#define GSR_PIN 26  // GPIO ADC ESP32 (32–39)

extern float gsr_value;

void gsr_init();
void gsr_read(unsigned int nilai_millis);

#endif