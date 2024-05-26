const  byte  LDR1= A0;  //光敏電阻分壓輸入腳
const  byte  led = 13;  //LED燈輸出腳
int  readLDR1=0;  //光敏電阻電壓值

void  setup() {
  analogReadResolution(14);  // 變更解析度為 14 位元
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void  loop() {
  readLDR1=analogRead(LDR1);  //讀取光敏電阻類比電壓輸入
  Serial.print("類比電壓: ");
  Serial.println(readLDR1);
  
  if (readLDR1 >= 13500) { 
    digitalWrite(led, HIGH);  // LED亮
  } else {    
    digitalWrite(led, LOW);  // LED暗
  }

  delay(1000);
}

