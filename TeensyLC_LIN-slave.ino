// https://github.com/MarkusLange/Teensy_3.x_4.x_and_LC_LIN_Master
// https://www.skpang.co.uk/collections/breakout-boards/products/lin-bus-breakout-board
// https://developerhelp.microchip.com/xwiki/bin/view/applications/lin/data-link-layer/
// https://linchecksumcalculator.machsystems.cz/

int linCS = 14;
uint8_t SYNC = 0x00;
uint8_t PID = 0x00;
uint8_t response[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
uint8_t CRC = 0x49;  // with PID 0x50, LIN 2.x, enhanced checksum

void setup() {
  pinMode(linCS, OUTPUT);
  digitalWrite(linCS, HIGH);  // enable MCP2004
  Serial2.begin(19200);       // init hardware serial port #2
}

void loop() {
  while (SYNC != 0x55) {             // scan serial bus for SYNC byte
    while (!Serial2.available()) {}  // wait for serial data to become available
    SYNC = Serial2.read();           // read 1 byte from serial
  }                                  // exit while loop and proceed when SYNC byte detected

  while (!Serial2.available()) {}  // wait for serial data to become available again
  PID = Serial2.read();            // read PID byte that will follow SYNC byte

  if (PID == 0x50) {             // check whether we are addressed
    Serial2.write(response, 8);  // if so, send 8 byte response
    Serial2.write(CRC);          // and send CRC byte
  }                              // if not then loop for next LIN frame
  SYNC = 0x00;                   // reset SYNC variable for next loop
}
