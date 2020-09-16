#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT)
  ; Serial.begin(38400);
  while (!Serial) {
    ;
  }
  digitalWrite(PIN_LED,0);
  delay(1000);
  int i = 0;
  while (i < 5) {
    digitalWrite(PIN_LED, 1);
    delay(100);
    digitalWrite(PIN_LED, 0);
    delay(100);
    i += 1;
  }
  while(1){
    digitalWrite(PIN_LED, 1);
  }
}

void loop() {
}
