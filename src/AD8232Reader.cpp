#include "../header/AD8232Reader.h"

int ecg_value;
float ecg_sum = 0.0;
float ecg_avg = 0.0;
uint16_t ecg_fast_count = 0;

void ecg_init()
{
  // Konfigurasi ADC ESP32
  analogReadResolution(12);          // 12-bit (0–4095)
  analogSetAttenuation(ADC_11db);    // Full range ~0–3.3V

  pinMode(SENSOR_PIN, INPUT);
}

void ecg_read(unsigned int nilai_millis)
{
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 10) return;

  prevMillis = nilai_millis;

  ecg_value = analogRead(SENSOR_PIN);

  ecg_sum += ecg_value;
  ecg_fast_count++;
}
