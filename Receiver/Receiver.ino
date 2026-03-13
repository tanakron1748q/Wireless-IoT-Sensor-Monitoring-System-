#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

struct SensorData {
  float temperature;
  float humidity;
  int mq2Value;
  long distance;
};

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.println("Receiver started...");
}

void loop() {
  if (radio.available()) {
    SensorData data;
    radio.read(&data, sizeof(data));

    // ส่งออก Serial ตาม Format ที่ Node.js ต้องการ
    Serial.print("Temperature: ");
    Serial.println(data.temperature);

    Serial.print("Humidity: ");
    Serial.println(data.humidity);

    Serial.print("MQ2 Value: ");
    Serial.println(data.mq2Value);

    Serial.print("Distance: ");
    Serial.println(data.distance);

    Serial.println(); // เว้นบรรทัดเพื่อแยก Packet
  }
}
