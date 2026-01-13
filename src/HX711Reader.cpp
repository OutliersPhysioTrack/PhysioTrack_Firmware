#include "../header/HX711Reader.h"

// OBJECT HX711
HX711 scale;

// VARIABLE GLOBAL
float loadcell_kg = 0.0;
float loadcell_sum = 0.0;
uint16_t loadcell_count = 0;

// FAKTOR KALIBRASI
// GANTI SESUAI HASIL KALIBRASI
float calibration_factor = -7050.0;

// INIT HX711
void hx711_init()
{
  scale.begin(HX711_DT_PIN, HX711_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();   // nol-kan beban awal
}

// TARE ULANG
void hx711_tare()
{
  scale.tare();
}

// BACA BERAT
void hx711_read(unsigned int nilai_millis)
{
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 100) return;
  prevMillis = nilai_millis;

  // BACA NILAI LOADCELL
  if (scale.is_ready()) {
    float berat = scale.get_units(5);  // rata-rata 5 sampel
    loadcell_kg = berat;
  }

  loadcell_sum = loadcell_kg;
  loadcell_count++;
}
