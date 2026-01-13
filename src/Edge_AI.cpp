#include "header/Edge_AI.h"

#include <PhysioTrack_inferencing.h>

// buffer untuk fitur (input model)
static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

// EDGE IMPULSE: RUN CLASSIFIER
// Input: heartRate, spo2, dht11_temp_value, dht11_hum_value, ds18b20_value, gsr_value, loadcell_kg
// Output: label + confidence tertinggi
bool run_edge_impulse(int32_t heartRate_value, int32_t spo2_value, float ds18b20_value, 
                      float gsr_value, int ecg_value, float loadcell_kg, 
                      float dht11_temp_value, float dht11_hum_value,
                      String &best_label, float &best_conf) {
  // EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE bisa >2,
  // untuk contoh sederhana, kita isi awal dengan temp & hum, sisanya 0.
  for (size_t i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++) {
    features[i] = 0.0f;
  }

  if (EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE >= 2) {
    features[0] = heartRate_value;
    features[1] = spo2_value;
    features[2] = ds18b20_value;
    features[3] = gsr_value;
    features[4] = ecg_value;
    features[5] = loadcell_kg;
    features[6] = dht11_temp_value;
    features[7] = dht11_hum_value;
  }

  signal_t signal;
  int err = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0) {
    Serial.print("signal_from_buffer error: ");
    Serial.println(err);
    return false;
  }

  ei_impulse_result_t result = { 0 };

  // false = no debug
  EI_IMPULSE_ERROR ei_err = run_classifier(&signal, &result, false);
  if (ei_err != EI_IMPULSE_OK) {
    Serial.print("run_classifier error: ");
    Serial.println(ei_err);
    return false;
  }

  // Cari label dengan nilai paling tinggi
  size_t best_i = 0;
  best_conf = 0.0f;
  for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
    if (result.classification[i].value > best_conf) {
      best_conf = result.classification[i].value;
      best_i = i;
    }
  }

  best_label = String(result.classification[best_i].label);
  return true;
}