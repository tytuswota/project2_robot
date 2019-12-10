#include "UltrasonicSensor.cpp"

#define TRIG_FRONT 4
#define ECHO_FRONT 2

volatile unsigned long pulseTimeFront;
UltrasonicSensor *usFront;

void isrFront() {
  static unsigned long int start;
  if(digitalRead(ECHO_FRONT)) {
    start = micros();
  } else {
    pulseTimeFront = micros()-start;
  }
  usFront->pulse();
}

void setup() {
  Serial.begin(9600);
  usFront = new UltrasonicSensor(TRIG_FRONT, ECHO_FRONT, &pulseTimeFront, isrFront);
  usFront->pulse();
}

void loop() {
  Serial.println(usFront->getLastDistance());
}
