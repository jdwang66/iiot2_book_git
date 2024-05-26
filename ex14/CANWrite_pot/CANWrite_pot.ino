#include <Arduino_CAN.h>

static uint32_t const CAN_ID = 0x20;
const int POT = A0;

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  if (!CAN.begin(CanBitRate::BR_250k))
  {
    Serial.println("CAN.begin(...) failed.");
    for (;;) {}
  }

  analogReadResolution(14);
  delay(1000);
}

void loop()
{ 
  uint16_t val = analogRead(POT);
  uint8_t val1 = val / 256;
  uint8_t val2 = val % 256;
  Serial.print("CAN ID: ");
  Serial.print(CAN_ID);
  Serial.print(" , ");  
  Serial.print("Analog Reading: ");
  Serial.println(val); 

  uint8_t const msg_data[] = {0x00,0x00,0,0,0,0,0,0};  
  memcpy((void *)(msg_data), &val1, sizeof(val1));
  memcpy((void *)(msg_data+1), &val2, sizeof(val2));
  CanMsg const msg(CanStandardId(CAN_ID), sizeof(msg_data), msg_data);

  if (int const rc = CAN.write(msg); rc < 0)
  {
    Serial.print  ("CAN.write(...) failed with error code ");
    Serial.println(rc);
    for (;;) { }
  }
  delay(2000);
}
