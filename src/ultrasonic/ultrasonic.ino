#include "UltrasonicSensor.cpp"

#define TRIG_FRONT 4
#define ECHO_FRONT 2

int pulseTimeFront;

void isrFront() {
  static unsigned long int start;
  if(digitalRead(ECHO_FRONT)) {
    start = micros();
  } else {
    pulseTimeFront = micros()-start;
  }
}

UltrasonicSensor usFront(TRIG_FRONT, ECHO_FRONT, &pulseTimeFront, isrFront);

void setup() {
  Serial.begin(9600);
}

void loop() {
  usFront.pulse();
  Serial.println(usFront.getDistance());
}
