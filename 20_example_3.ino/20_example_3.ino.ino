#include <Servo.h>

// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10

#define _DIST_ALPHA 0.2 // EMA weight of new sample (range: 0 to 1)

int a, b; // unit: mm
float dist_ema, alpha; // unit: mm
int duty_target;
Servo myservo;

void setup() {
// initialize GPIO pins
  // pinMode(PIN_LED,OUTPUT);
  // digitalWrite(PIN_LED, 1);

  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(900);

  alpha = _DIST_ALPHA;
  
// initialize serial port
  Serial.begin(57600);

  a = 68;
  b = 400;
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  dist_ema = alpha*dist_cali + (1-alpha)*dist_ema;
  Serial.print("min:0,max:500,");
  Serial.print("raw_dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_ema:");
  Serial.print(dist_ema);
  Serial.print(", duty_target:");
  Serial.println(duty_target);
  duty_target = map(dist_ema, 600, 100, 750, 1000);
  myservo.writeMicroseconds(duty_target);
  delay(5);
}
