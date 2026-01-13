# ESP32 Multi-Sensor Health/Environment Monitor (Edge AI + MQTT)

Firmware ESP32 untuk membaca beberapa sensor biometrik & lingkungan, menjalankan klasifikasi **Edge Impulse (on-device)**, lalu mengirim data ke broker **MQTT** dalam format JSON. Sistem juga memiliki **buzzer non-blocking** yang berbunyi berdasarkan label prediksi (`safe / warning / danger`).

---

## Fitur Utama
- Baca multi-sensor secara periodik (non-blocking berbasis `millis`).
- Inferensi **Edge Impulse** di ESP32 (label + confidence).
- Publish data sensor + hasil ML ke **MQTT** (JSON).
- **Buzzer non-blocking**:
  - `safe`  → silent
  - `warning` → 2 beep
  - `danger` → 3 beep
- Serial log untuk debugging.

---

## Sensor & Modul yang Digunakan
1. **MAX30102** 
   - Heart Rate & SpO2

2. **AD8232**  
   - ECG (single lead)

3. **DS18B20**   
   - Suhu tubuh/permukaan

4. **HX711 + Load Cell**  
   - Berat (kg)

5. **DHT11**  
   - Suhu & kelembapan lingkungan

6. **GSR Sensor** 
   - Galvanic Skin Response

7. **Buzzer**  
   - Alert berdasarkan label Edge AI

---



