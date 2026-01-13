#ifndef EDGE_AI_H
#define EDGE_AI_H

#include <Arduino.h>
#include <stdint.h>

// EDGE IMPULSE CONFIG
// Include dari Edge Impulse Arduino Library
// GANTI sesuai nama file header project Anda dari Edge Impulse

// EDGE IMPULSE: RUN CLASSIFIER
bool run_edge_impulse(int32_t heartRate_value, int32_t spo2_value, float ds18b20_value, 
                      float gsr_value, int ecg_value, float loadcell_kg, 
                      float dht11_temp_value, float dht11_hum_value,
                      String &best_label, float &best_conf);

#endif