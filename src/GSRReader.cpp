#include "../header/GSRReader.h"

float gsr_value;
float gsr_sum = 0.0;
float gsr_avg = 0.0;
uint16_t gsr_fast_count = 0;

void gsr_init()
{
  // Konfigurasi ADC ESP32
  analogReadResolution(12);          // 12-bit (0–4095)
  analogSetAttenuation(ADC_11db);    // Full range ~0–3.3V

  pinMode(GSR_PIN, INPUT);
}

void gsr_read(unsigned int nilai_millis)
{
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 10) return;

  prevMillis = nilai_millis;

  // BACA NILAI GSR
  gsr_value = analogRead(GSR_PIN);
  
  gsr_sum += gsr_value;
  gsr_fast_count++;
}