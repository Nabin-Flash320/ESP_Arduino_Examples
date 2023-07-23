
#define DEFAULT_LED_PIN RGB_BUILTIN

void setup() {
  pinMode(DEFAULT_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(DEFAULT_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(DEFAULT_LED_PIN, LOW);
  delay(1000);
}


