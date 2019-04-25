
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
const byte address[6] = "00001";
int currentDispenser = 0;



int getAIMove() {
  return random(6) + 'a';
}

void humanMove(int move) {

}

void setup() {
  Serial.begin(115200);
  // Serial.println("Starting Shin Ramyun AI Master ...");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.openWritingPipe(address);
  radio.startListening();
}


void moveHandler(int data) {
  Serial.println(String((char)data) + "," + String((char)(currentDispenser + 'x')));

  while (true) {
    while (!Serial.available()) {}
    while (radio.available()) {
      int garbage = 0;
      radio.read(&garbage, sizeof(garbage));
    }
    String resp = Serial.readString();
    if (resp[0] == 'Z') {
      break;
    }
  }

  currentDispenser = (currentDispenser + 1) % 2;
}

void loop() {
  if (radio.available()) {
    int data;

    radio.read(&data, sizeof(data));

    moveHandler(data);
    humanMode(data);

    moveHandler(getAIMove());

  }
}
