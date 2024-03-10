// https://github.com/MarkusLange/Teensy_3.x_4.x_and_LC_LIN_Master
// https://www.skpang.co.uk/collections/breakout-boards/products/lin-bus-breakout-board
// https://developerhelp.microchip.com/xwiki/bin/view/applications/lin/data-link-layer/
// https://linchecksumcalculator.machsystems.cz/

// comment line 463 of lin-bus.cpp like so: //_stream->read();

#include "lin_bus.h"

int linCS = 23;
uint8_t linRXdata[8];
uint8_t CRC;
uint8_t ID = 0x10;  // PID = 0x50

LIN lin;

void setup() {
  pinMode(linCS, OUTPUT);
  digitalWrite(linCS, HIGH);
  lin.begin(&Serial3, 19200);
}

void loop() {
  CRC = lin.response(ID, linRXdata, 8, lin2x);
  Serial.printf("CRC: 0x%X   ", CRC);
  Serial.print("data: ");
  for (int i = 0; i < 8; i++) {
    Serial.printf("0x%.2X ", linRXdata[i]);
  }
  Serial.println();
  delay(1000);
}
