#include <ModbusRTUSlave.h>

const  int  POT=A0;

ModbusRTUSlave modbus(Serial1);
uint16_t holdingRegisters[1];

void setup() {
  Serial.begin(9600);
  modbus.configureHoldingRegisters(holdingRegisters, 1);
  modbus.begin(1, 38400);  // SlaveId = 1, buad = 38400
  analogReadResolution(14);
}

void loop() {
  int  val = analogRead(POT);
  Serial.print("Voltage: ");
  Serial.println(val);
  holdingRegisters[0]=val;
  modbus.poll();
  delay(1000);
}


