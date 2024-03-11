// https://github.com/MarkusLange/Teensy_3.x_4.x_and_LC_LIN_Master
// https://www.skpang.co.uk/collections/breakout-boards/products/lin-bus-breakout-board
// https://developerhelp.microchip.com/xwiki/bin/view/applications/lin/data-link-layer/
// https://linchecksumcalculator.machsystems.cz/

elapsedMicros BreakLength;  // define timer

bool WaitForBreakStart = true;  // first state of ISR
bool WaitForBreakEnd = false;   // second state of ISR
bool ValidLINbreak = false;     // set if valid LIN break detected
int linCS = 14;
int RXpin = 9;
uint8_t SYNC = 0x00;
uint8_t PID = 0x00;
uint8_t response[8] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
uint8_t CRC = 0x49;  // calculated with PID 0x50 [LIN 2.x, enhanced checksum]

void setup() {
  pinMode(linCS, OUTPUT);                                        // CS pin of MCP2004
  digitalWrite(linCS, HIGH);                                     // enable MCP2004
  Serial2.begin(19200);                                          // init hardware serial port #2
  attachInterrupt(digitalPinToInterrupt(RXpin), RXisr, CHANGE);  // attach to Serial2 RX pin 9
}

void loop() {
  if (ValidLINbreak) {               // if valid LIN break detected
    while (!Serial2.available()) {}  // wait for serial data to become available
    SYNC = Serial2.read();           // read SYNC byte from serial
    while (!Serial2.available()) {}  // wait for serial data to become available again
    PID = Serial2.read();            // read PID byte that will follow SYNC byte
    if (PID == 0x50) {               // check whether we are addressed
      Serial2.write(response, 8);    // if so, send 8 byte response
      Serial2.write(CRC);            // and send CRC byte
    }                                //
    ValidLINbreak = false;           // reset bool
    WaitForBreakStart = true;        // set first state for RXisr
  }
}

void RXisr() {
  if (WaitForBreakStart) {                // first state
    if (digitalReadFast(RXpin) == LOW) {  // if low
      BreakLength = 0;                    // start timer
      WaitForBreakStart = false;          // reset this state
      WaitForBreakEnd = true;             // and go to second state
    }
  }
  if (WaitForBreakEnd) {                                 // second state
    if (digitalReadFast(RXpin) == HIGH) {                // if high, check break time
      if ((BreakLength > 600) && (BreakLength < 800)) {  // if break time in valid range [usec]
        WaitForBreakEnd = false;                         // reset this state
        ValidLINbreak = true;                            // and set bool to be checked by loop()
      } else {                                           // if break time not in valid range
        WaitForBreakEnd = false;                         // reset this state
        WaitForBreakStart = true;                        // and go to previous state
      }                                                  //
      Serial2.clear();                                   // clear serial buffer from any garbage
    }
  }
}
