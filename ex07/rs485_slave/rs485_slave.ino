const  int  LED=9;
uint8_t led_pwm[] = {
  0,     1,   2,   3,   4,   5, 
  7,    10,  13,  15,  19,  24, 
  26,   32,  38,  45,  52, 
  57,   66,  75,  85,  96, 
  108, 121, 134, 149, 164, 
  181, 198, 216, 235, 255
};

void  setup() {
	Serial.begin(9600);  
  Serial1.begin(9600);  // RS485
  pinMode(LED, OUTPUT);
}

void  loop() {

  while(Serial1.available()) {
    int  val = Serial1.parseInt();        // Read RS485
	  int  index=map(val, 0, 16383, 0, 31); // 限制在 0~31

    Serial.print("Analog Reading: ");     // 輸出資料至序列埠
	  Serial.println(led_pwm[index]);       // 顯示 PWM 值
	  analogWrite(LED, led_pwm[index]);     // LED PWM 調光
	  delay(100);                           // 等待 0.1 秒
  }	
}

