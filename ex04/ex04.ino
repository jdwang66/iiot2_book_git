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
	pinMode(LED, OUTPUT);
}

void  loop() {
	for (int i = 0; i < 32; i++) {
		analogWrite(LED, led_pwm[i]);  // LED由暗變亮
		delay(100);
	}
	for (int i = 31; i >= 0; i--) {
		analogWrite(LED, led_pwm[i]);  //LED由亮變暗
		delay(100);
	}
}
