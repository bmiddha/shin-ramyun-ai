#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Adafruit_MCP23017.h"
#include <LiquidCrystal.h>

const byte RS = 10, E  = 9, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
const byte columnButtons[7] = { 2, 3, 4, 5, 6, 7, 8 };
const byte btnA = 0, btnB = 1;
const byte address[6] = "00001";

RF24 radio(7, 8);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
Adafruit_MCP23017 mcp;

void sendRF(int btn) {
  int data;
  if (btn <= 8 && btn >= 2) data = ('a' + (8 - btn));
  if (btn <= 1 && btn >= 0) data = ('x' + (1 - btn));
  Serial.println(data);
  radio.write(&data, sizeof(data));
}

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.print(" Shin Ramyun Ai ");
  lcd.setCursor(0,1);
  lcd.print("=== Connect4 ===");

  mcp.begin();

  for (int i = 0; i <= 9; i++) {
    mcp.pinMode(i, INPUT);
    mcp.pullUp(i, HIGH);
  }

  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    if (mcp.digitalRead(i) == LOW) sendRF(i);
  }
}
