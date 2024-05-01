#include <ModbusRTUMaster.h>

const  int  LED=9;
uint8_t led_pwm[] = {
  0,     1,   2,   3,   4,   5, 
  7,    10,  13,  15,  19,  24, 
  26,   32,  38,  45,  52, 
  57,   66,  75,  85,  96, 
  108, 121, 134, 149, 164, 
  181, 198, 216, 235, 255
};

ModbusRTUMaster modbus(Serial1);
uint16_t holdingRegisters[8];

void setup() {
  Serial.begin(9600);
  modbus.begin(38400); 

}

void loop() {
  modbus.readHoldingRegisters(1, 0, holdingRegisters, 1);
  int val=holdingRegisters[0];
  int index=map(val, 0, 16383, 0, 31);
  Serial.print("LED PWM:");
  Serial.println(led_pwm[index]);
  analogWrite(LED, led_pwm[index]);
  delay(1000);
}
