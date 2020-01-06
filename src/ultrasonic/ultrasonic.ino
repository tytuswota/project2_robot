#include "UltrasonicSensor.cpp"

#define TRIG_FRONT 4
#define ECHO_FRONT 2

volatile unsigned long pulseTimeFront;
UltrasonicSensor *usFront;

int readings[5];
byte readingpos;

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

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
  readings[readingpos++] = usFront->getLastDistance();
  if(readingpos == 4) {
    readingpos = 0;
    qsort(readings, 4, sizeof(int), cmp);
    if(readings[2] < 50) Serial.println("object detected");
  }
}
