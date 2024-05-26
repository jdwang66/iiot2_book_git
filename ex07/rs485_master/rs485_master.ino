const  int  POT=A0;
void  setup() {
	Serial.begin(9600);           // 序列埠監控傳輸速度9600 bps
  Serial1.begin(9600);          // RS485
  analogReadResolution(14);  
}
void  loop() {
	int  val = analogRead(POT);   //讀取A0類比輸入值
  Serial.print("Voltage: ");
	Serial.println(val);
  Serial1.println(val);
	delay(1000);                  // 等待1秒
}

