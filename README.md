# Teensy-based LIN-bus Master & Slave
This repository shows a simple Teensy-based LIN-bus Master &amp; Slave setup.

For the Master I used this [library](https://github.com/MarkusLange/Teensy_3.x_4.x_and_LC_LIN_Master). 

The Slave code is a very basic hardware serial port handler. When it receives a specific message from the Master, it responds with a defined message & checksum.

For calculating the checksum needed by the Slave, I used this [tool](https://linchecksumcalculator.machsystems.cz/).

![image](https://github.com/psitech/Teensy-based-LIN-bus-Master-Slave/assets/27091013/f76b1dff-182d-4fc1-a23a-dc019dd74ff6)


The test setup:

![image](https://github.com/psitech/Teensy-based-LIN-bus-Master-Slave/assets/27091013/7442f885-6551-4b2e-87df-74b9e2bedee7)


The LIN message frame as seen on the RX pin of the Master:

![image](https://github.com/psitech/Teensy-based-LIN-bus-Master-Slave/assets/27091013/a518352a-a7fb-4236-b1ca-b61e4781c8a5)

The serial monitor of the Arduino IDE shows:

![image](https://github.com/psitech/Teensy-based-LIN-bus-Master-Slave/assets/27091013/498b100d-62da-4ef4-91f2-6d53d5193fa4)
