#include <Servo.h>

// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10

#define _DIST_ALPHA 0.2 // EMA weight of new sample (range: 0 to 1)

int a, b; // unit: mm
float dist_ema, alpha; // unit: mm
Servo myservo;

void setup() {
// initialize GPIO pins
  // pinMode(PIN_LED,OUTPUT);
  // digitalWrite(PIN_LED, 1);

  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(1100);

  alpha = _DIST_ALPHA;
  
// initialize serial port
  Serial.begin(57600);

  a = 68;
  b = 650;
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
  Serial.print(",dist_cali:");
  Serial.print(dist_cali);
  Serial.print(",dist_ema:");
  Serial.println(dist_ema);
  //if(raw_dist > 156 && raw_dist <224) digitalWrite(PIN_LED, 0);
  //else digitalWrite(PIN_LED, 255);
  if (dist_ema < 255) myservo.writeMicroseconds(1125);
  else if (dist_ema > 255) myservo.writeMicroseconds(1000);
  else myservo.writeMicroseconds(1100);
  delay(5);
}
