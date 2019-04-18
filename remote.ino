/*

*/

#include <RF24.h>
#include "Adafruit_MCP23017.h"
#include <LiquidCrystal.h>

// PINOUTS
const byte RS = 10, E  = 9, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
const byte columnButtons[7] = { 2, 3, 4, 5, 6, 7, 8 };
const byte btnA = 0, btnB = 1;
const byte address = 0101;

RF24 radio(7,8);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
Adafruit_MCP23017 mcp;

void sendButtonRF(byte btn) {
  
}

void updateLcd (char* string) {
  
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting Shin Ramyun AI Remote ...");
    
    lcd.begin(16, 2);
    lcd.print("Hi");
    
    mcp.begin();
    
    for(int i = 0; i <= 9; i++) {
      mcp.pinMode(i, INPUT);
      mcp.pullUp(i,HIGH);
    }
    
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.openWritingPipe(address);
    radio.startListening();
    radio.printDetails();
}

void loop() {
  for(int i = 0; i <= 9; i++) {
    if(mcp.digitalRead(i) == LOW) Serial.println(i);
  }
}
