// inout library
#include <Arduino.h>
#include "header/MAX30102Reader.h"
#include "header/AD8232Reader.h"
#include "header/DS18B20Reader.h"
#include "header/HX711Reader.h"
#include "header/DHT11Reader.h"
#include "header/GSRReader.h"
#include "header/Edge_AI.h"
#include "header/mqtt_iot.h"

//input extern variable
extern int32_t heartRate_value;
extern int32_t spo2_value;
extern float dht11_temp_value;
extern float dht11_hum_value;
extern float ds18b20_value;
extern float gsr_value;
extern float loadcell_kg;
extern int ecg_value;

extern float conf;
extern String label;

extern String payload;

// label dan confidence dari edge impulse
// extern String label;
// extern float conf;

void setup()
{
  Serial.begin(115200);

  // setup sensor
  ecg_init();
  gsr_init();
  max30102_init();
  ds18b20_init();
  hx711_init();
  dht11_init();

  // wifi
  setupWiFi();
  Serial.println("\nWiFi connected");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
}

void loop()
{
  // Pastikan MQTT tetap connect
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // millis untuk interval baca sensor
  unsigned long startMillis = millis();

  /*****baca nilai sensor****/
  // baca sensor cepat
  ecg_read(startMillis);
  gsr_read(startMillis);

  // baca sensor sedang
  hx711_read(startMillis);

  // baca sensor lambat
  ds18b20_read(startMillis);
  dht11_hum_read(startMillis);
  dht11_temp_read(startMillis);
  
  // baca max30102
  max30102_read(startMillis);

  // membaca sensor ke serial monitor
  // baca_sensor();

  static unsigned long lastPublish = 0;
  if (startMillis - lastPublish > 2000) {
    // Jalankan model Edge Impulse
    bool ok = run_edge_impulse(heartRate_value, spo2_value, ds18b20_value, 
                                gsr_value, ecg_value, loadcell_kg, 
                                dht11_temp_value, dht11_hum_value,
                                label, conf);

    // jika edge ai bekerja maka print ML prediction
    if (ok) {
      Serial.println("ML Prediction");
    } else {
      Serial.println("Gagal menjalankan Edge Impulse");
    }

    // membuat json dan mengirim mqtt
    make_json();

    client.publish(topicSensorOut, payload.c_str());
    
    // informasi mqtt
    Serial.println("Published");
    Serial.print(topicSensorOut);
    Serial.print(" => ");
    Serial.println(payload);
    
    lastPublish = startMillis;
  }
}