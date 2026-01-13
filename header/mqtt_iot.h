#ifndef MQTT_IOT_H
#define MQTT_IOT_H

#include <WiFi.h>
#include <PubSubClient.h>

#include "header/MAX30102Reader.h"
#include "header/AD8232Reader.h"
#include "header/DS18B20Reader.h"
#include "header/HX711Reader.h"
#include "header/DHT11Reader.h"
#include "header/GSRReader.h"

extern const char* ssid;
extern const char* password;

extern const char* mqtt_server;
extern const int   mqtt_port;

extern const char* topicSensorOut;
extern const char* topicOutputIn;

extern WiFiClient espClient;
extern PubSubClient client;

extern String payload;
extern float conf;
extern String label;

void mqttCallback(char* topic, byte* payload, unsigned int length);
void setupWiFi();
void reconnectMQTT();
void make_json();
void baca_sensor();

#endif
