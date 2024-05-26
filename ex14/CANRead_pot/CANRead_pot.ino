#include <Arduino_CAN.h>

const  int  LED=9;

uint8_t led_pwm[] = {
  0,     1,   2,   3,   4,   5, 
  7,    10,  13,  15,  19,  24, 
  26,   32,  38,  45,  52, 
  57,   66,  75,  85,  96, 
  108, 121, 134, 149, 164, 
  181, 198, 216, 235, 255
};

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  if (!CAN.begin(CanBitRate::BR_250k))
  {
    Serial.println("CAN.begin(...) failed.");
    for (;;) {}
  }

  pinMode(LED, OUTPUT);  
}

uint8_t val1;
uint8_t val2;
uint16_t val3;

void loop()
{
  if (CAN.available())
  {
    CanMsg const msg = CAN.read();
    Serial.print("CAN ID: ");
    Serial.print(msg.id);
    Serial.print(" , ");
    val1 = msg.data[0];
    val2 = msg.data[1];
    val3=val1*256+val2;
    Serial.print("Voltage: ");
    Serial.println(val3);

    int per=map(val3, 0, 16383, 0, 31);
    analogWrite(LED, led_pwm[per]);
    delay(100);    
  }
}
