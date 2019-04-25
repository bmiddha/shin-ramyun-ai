
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
const byte address[6] = "00001";
int currentDispenser = 0;

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
    Serial.println(String(data) + "," + String((currentDispenser+'x')));
    while (true) {
        while (!Serial.available()) {}
        while (radio.available()) {
            int garbage = 0;
            radio.read(&garbage, sizeof(data));
        }
        char resp = Serial.read();
        if (resp == 'z') {
            break;
        }
    }
    int nextCol = random(6) + 'a';
    currentDispenser = (currentDispenser + 1)%2;
    Serial.println(String(data) + "," + String((currentDispenser+'x')));
    while (true) {
        while (!Serial.available()) {}
        while (radio.available()) {
            int garbage = 0;
            radio.read(&garbage, sizeof(data));
        }
        char resp = Serial.read();
        if (resp == 'z') {
            break;
        }
    }
    currentDispenser = (currentDispenser + 1)%2;
  }
}
