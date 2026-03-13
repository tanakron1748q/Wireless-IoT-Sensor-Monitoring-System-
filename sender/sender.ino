#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
int TRIG_PIN = 5;
int ECHO_PIN = 6;
int mq2Pin = A0;

DHT dht(DHTPIN, DHTTYPE);
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

struct SensorData {
  float temperature;
  float humidity;
  int mq2Value;
  long distance;
};

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  SensorData data;
  readDHT(&data.temperature, &data.humidity);
  data.mq2Value = MQ2Function();
  data.distance = UltrasonicFunction();

  Serial.print("Sending -> ");
  Serial.print("Temp: "); Serial.print(data.temperature);
  Serial.print(" | Humi: "); Serial.print(data.humidity);
  Serial.print(" | MQ2: "); Serial.print(data.mq2Value);
  Serial.print(" | Dist: "); Serial.println(data.distance);

  bool ok = radio.write(&data, sizeof(data));

  if (!ok) {
    Serial.println("Send failed!");
  }

  delay(1000);
}

int UltrasonicFunction() {
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
  delay(200);
  return distance;
}

int MQ2Function() {
  int sensorValue = analogRead(mq2Pin);
  delay(200);
  return sensorValue;
}

void readDHT(float* temperature, float* humidity) {
  *humidity = dht.readHumidity();
  *temperature = dht.readTemperature();

  if (isnan(*humidity) || isnan(*temperature)) {
    Serial.println("Failed to read DHT!");
    *humidity = 0;
    *temperature = 0;
  }
}
