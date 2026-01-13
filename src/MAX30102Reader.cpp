#include "../header/MAX30102Reader.h"

// PIN I2C ESP32
#define SDA_PIN 21
#define SCL_PIN 22

// DEFINISI VARIABLE
MAX30105 particleSensor;

uint32_t irBuffer[BUFFER_LENGTH];
uint32_t redBuffer[BUFFER_LENGTH];

// OUTPUT VARIABLE
int32_t spo2_value;
int32_t heartRate_value;

// VALIDITY FLAG
int8_t  validSPO2;
int8_t  validHeartRate;

// INIT SENSOR
void max30102_init() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor MAX30102 tidak terdeteksi");
  }

  particleSensor.setup(
    60,   // LED brightness
    4,    // sample average
    2,    // Red + IR
    100,  // sample rate
    411,  // pulse width
    4096  // ADC range
  );

  max30102_read_first();
}

// BACA 100 DATA PERTAMA
void max30102_read_first() {
  for (uint8_t i = 0; i < BUFFER_LENGTH; i++) {
    while (!particleSensor.available()) {
      particleSensor.check();
    }

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i]  = particleSensor.getIR();
    particleSensor.nextSample();
  }

  maxim_heart_rate_and_oxygen_saturation(
    irBuffer,
    BUFFER_LENGTH,
    redBuffer,
    &spo2_value,
    &validSPO2,
    &heartRate_value,
    &validHeartRate
  );
}

// UPDATE DATA
void max30102_read(unsigned int nilai_millis) {
  static unsigned int prevMillis = 0;
  if(nilai_millis - prevMillis < 2000) return;
  prevMillis = nilai_millis;

  // Geser buffer
  for (uint8_t i = 25; i < BUFFER_LENGTH; i++) {
    redBuffer[i - 25] = redBuffer[i];
    irBuffer[i - 25]  = irBuffer[i];
  }

  // Ambil 25 data baru
  for (uint8_t i = 75; i < BUFFER_LENGTH; i++) {
    while (!particleSensor.available()) {
      particleSensor.check();
    }

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i]  = particleSensor.getIR();
    particleSensor.nextSample();
  }

  maxim_heart_rate_and_oxygen_saturation(
    irBuffer,
    BUFFER_LENGTH,
    redBuffer,
    &spo2_value,
    &validSPO2,
    &heartRate_value,
    &validHeartRate
  );

  if ((!validHeartRate) || (!validSPO2)) {
    heartRate_value = -100;
    spo2_value = -100;
  }
}
