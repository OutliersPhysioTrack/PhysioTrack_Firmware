#include "../header/mqtt_iot.h"

// WIFI CONFIG
const char* ssid     = "hai";
const char* password = "kitabisa12";

// MQTT CONFIG
const char* mqtt_server   = "broker.hivemq.com";
const int   mqtt_port     = 1883;

const char* topicSensorOut = "outliers/juara1/sensor";
const char* topicOutputIn  = "outliers/juara1/output";

// GLOBAL OBJECTS
WiFiClient espClient;
PubSubClient client(espClient);

// output terbaik
float conf   = 0.0f;
String label = "Unknown";

// PAYLOAD JSON
String payload;

// CALLBACK
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }

    Serial.print("[MQTT] Topic: ");
    Serial.print(topic);
    Serial.print(" | Message: ");
    Serial.println(msg);
    if (msg.indexOf("OPEN") != -1) {}
}

// WIFI CONNECT
void setupWiFi() {
    Serial.println("Menghubungkan WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
}

// MQTT RECONNECT
void reconnectMQTT() {
    while (!client.connected()) {
        Serial.println("Menghubungkan ke MQTT...");

        String clientId = "esp32_";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str())) {
            Serial.println("MQTT Connected!");
            client.subscribe(topicOutputIn);
        }
        else {
            Serial.print("Gagal, rc=");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void make_json() {
  payload = "{";
  payload += "\"device_id\":\"dev-001\",";
  payload += "\"hr\":" + String(heartRate_value) + ",";
  payload += "\"spo2\":" + String(spo2_value) + ",";
  // ECG bertipe int, dikirim sebagai float (dibagi 100 misalnya)
  payload += "\"ecg\":" + String((float)ecg_value / 100.0, 2) + ",";
  payload += "\"temp_ds18b20\":" + String(ds18b20_value, 1) + ",";
  payload += "\"dht_temp\":" + String(dht11_temp_value, 1) + ",";
  payload += "\"dht_hum\":" + String(dht11_hum_value, 1) + ",";
  payload += "\"gsr\":" + String(gsr_value, 0) + ",";
  payload += "\"loadcell_kg\":" + String(loadcell_kg, 1);
  payload += "\"label\":\"" + label + "\",";
  payload += "\"conf\":" + String(conf, 3);
  payload += "}";
}

void baca_sensor() {
//   Serial.print("HR: ");
//   Serial.print(heartRate_value);
//   Serial.print(" | SpO2: ");
//   Serial.print(spo2_value);

//   Serial.print(" | ECG: ");
//   Serial.print(ecg_value);

//   Serial.print(" | Temp: ");
//   Serial.print(ds18b20_value);

//   Serial.print(" | dht_temp: ");
//   Serial.print(dht11_temp_value);
//   Serial.print(" | dht_hum: ");
//   Serial.print(dht11_hum_value);
  
//   Serial.print(" | GSR: ");
//   Serial.print(gsr_value);

//   Serial.print(" | load_cell: ");
//   Serial.println(loadcell_kg);
}
