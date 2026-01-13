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

// ===================== BUZZER CONFIG =====================
static const int  BUZZER_PIN = 2;               
static const bool BUZZER_ACTIVE_HIGH = true;    

// ---------- buzzer non-blocking beeper ----------
struct Beeper {
  bool active = false;
  int beeps_left = 0;
  bool is_on = false;
  uint32_t last_ms = 0;

  static const uint32_t ON_MS  = 80;
  static const uint32_t OFF_MS = 80;

  void writePin(bool on) {
    if (BUZZER_ACTIVE_HIGH) digitalWrite(BUZZER_PIN, on ? HIGH : LOW);
    else                    digitalWrite(BUZZER_PIN, on ? LOW  : HIGH);
  }

  void stop() {
    active = false;
    beeps_left = 0;
    is_on = false;
    writePin(false);
  }

  void start(int count) {
    if (count <= 0) { stop(); return; }
    active = true;
    beeps_left = count;
    is_on = false;
    last_ms = millis();
    writePin(false);
  }

  void tick() {
    if (!active) return;

    uint32_t now = millis();
    if (!is_on) {
      if (now - last_ms >= OFF_MS) {
        is_on = true;
        last_ms = now;
        writePin(true);
      }
    } else {
      if (now - last_ms >= ON_MS) {
        is_on = false;
        last_ms = now;
        writePin(false);

        beeps_left--;
        if (beeps_left <= 0) stop();
      }
    }
  }
};

static Beeper beeper;

// ---------- label-based buzzer rules ----------
static void applyBuzzerByLabel(const String &lbl) {
  if (lbl.length() == 0) { beeper.stop(); return; }

  if (lbl.equalsIgnoreCase("safe")) {
    beeper.stop();
  } else if (lbl.equalsIgnoreCase("warning")) {
    beeper.start(2);
  } else if (lbl.equalsIgnoreCase("danger")) {
    beeper.start(3);
  } else {
    beeper.stop(); 
}
// =========================================================

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

void setup()
{
  Serial.begin(115200);

  // ===== buzzer init =====
  pinMode(BUZZER_PIN, OUTPUT);
  if (BUZZER_ACTIVE_HIGH) digitalWrite(BUZZER_PIN, LOW);
  else                    digitalWrite(BUZZER_PIN, HIGH);

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

  // mqtt
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
}

void loop()
{
  beeper.tick();

  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  unsigned long startMillis = millis();

  /***** baca nilai sensor ****/
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

  static unsigned long lastPublish = 0;
  if (startMillis - lastPublish > 2000) {

    bool ok = run_edge_impulse(heartRate_value, spo2_value, ds18b20_value,
                               gsr_value, ecg_value, loadcell_kg,
                               dht11_temp_value, dht11_hum_value,
                               label, conf);

    if (ok) {
      Serial.println("ML Prediction");
    } else {
      Serial.println("Gagal menjalankan Edge Impulse");
    }

    applyBuzzerByLabel(label);
    
    make_json();
    client.publish(topicSensorOut, payload.c_str());

    Serial.println("Published");
    Serial.print(topicSensorOut);
    Serial.print(" => ");
    Serial.println(payload);

    lastPublish = startMillis;
  }
}
