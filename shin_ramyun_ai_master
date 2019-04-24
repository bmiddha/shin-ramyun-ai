#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Shin Ramyun AI Master ...");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.openWritingPipe(address);
  radio.startListening();
}


void loop() {
  if (radio.available()) {
    int data;
    radio.read(&data, sizeof(data));
  }
}
