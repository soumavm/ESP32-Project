const byte led_gpio = 5;

void setup() {
  
}

void loop() {
  digitalWrite(led_gpio, HIGH);
  delay(1000);
  digitalWrite(led_gpio, LOW);  
  delay(1000);                       
}
