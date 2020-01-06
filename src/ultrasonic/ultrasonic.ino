#include "UltrasonicSensor.cpp"

long pulseTimeFront, pulseTimeUnder;
Ultrasonic usFront, usUnder;

void isrFront() {
  static unsigned long int start;
  if(digitalRead(usFront.echo)) {
    start = micros();
  } else {
    pulseTimeFront = micros()-start;
  }
  usUnder.pulse();
}

void isrUnder() {
  static unsigned long int start;
  if(digitalRead(usUnder.echo)) {
    start = micros();
  } else {
    pulseTimeUnder = micros()-start;
  }
}

ISR(TIMER1_COMPA_vect) {
  usFront.pulse();
}

void setTimerInterrupt() {
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 1562; // 16 000 000 / (prescaler * Hz) - 1
  
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler = 1024
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

long timeToMillimeters(long pulseTime) {
  return ((pulseTime >> 1) / 2.9);
}

void setup() {
  usFront = Ultrasonic(4, 2, isrFront);
  usUnder = Ultrasonic(5, 3, isrUnder);
  
  Serial.begin(9600);
  setTimerInterrupt();
}

void loop() {
  Serial.println("front: " + (String)timeToMillimeters(pulseTimeFront) + " under: " + (String)timeToMillimeters(pulseTimeUnder));
}