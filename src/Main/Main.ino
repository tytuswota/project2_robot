#define infraroodLinks 8
#define infraroodRechts 7

#define ultrasoonTrigVoor 11
#define ultrasoonEchoVoor 2
#define ultrasoonTrigOnder 12
#define ultrasoonEchoOnder 3

#define motorPin1A 9
#define motorPin1B 10
#define motorPin2A 4
#define motorPin2B 5

#include "motorController.cpp"
#include "UltrasonicSensor.cpp"

long timeToMillimeters(long pulseTime) {
  return ((pulseTime >> 1) / 2.9);
}

UltrasonicSensor usVoor, usOnder;
volatile unsigned long pulseTimeVoor;
volatile unsigned long pulseTimeOnder;

void startTimerInterruptLoop() {
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

ISR(TIMER1_COMPA_vect) {
  usVoor.pulse();
}

void isrVoor() {
  static unsigned long start;
  if(digitalRead(usVoor.echo)) {
    start = micros();
  } else {
    pulseTimeVoor = micros()-start;
  }
  usOnder.pulse();
}

void isrOnder() {
  static unsigned long start;
  if(digitalRead(usOnder.echo)) {
    start = micros();
  } else {
    pulseTimeOnder = micros()-start;
  }
}

motorController motor(motorPin1A, motorPin1B, motorPin2A, motorPin2B);

unsigned long int prevMillis = millis();

void setup() {
  Serial.begin(9600);
  pinMode(infraroodLinks, INPUT_PULLUP);
  pinMode(infraroodRechts, INPUT_PULLUP);
  usOnder = UltrasonicSensor(ultrasoonTrigOnder, ultrasoonEchoOnder, isrOnder);
  usVoor = UltrasonicSensor(ultrasoonTrigVoor, ultrasoonEchoVoor, isrVoor);
  startTimerInterruptLoop();
}

void loop() {
  

  int infraroodLinksVal = digitalRead(infraroodLinks);
  int infraroodRechtsVal = digitalRead(infraroodRechts);

  if (timeToMillimeters(pulseTimeVoor) < 50 && millis() > prevMillis + 200) {
    int x = 0;
    while (x < 50) {
    /*while (x < 50 usVoor->getLastDistance() < 50) {
      motor.motorStop();
      motor.motorSpinABackward();
      motor.motorSpinBForward();
      x++;
    }*/
    prevMillis = millis();
  }
  }
  else if (timeToMillimeters(pulseTimeOnder) > 100 && millis() > prevMillis + 200) {
    /*while (usOnder->getLastDistance() > 100) {
      motor.motorStop();
      prevMillis = millis();
    }*/
  }
  else {
    if (infraroodLinksVal == 1 && infraroodRechtsVal != 1) {
      motor.motorB("backward");
      motor.motorA("forward");
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal != 1) {
      motor.motorA("backward");
      motor.motorB("forward");
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal == 1) {
      for(int i = 0; i<150; i++){
        motor.motorA("backward");
        motor.motorB("backward");
      }
    }
    else 
    {
      motor.motorA("forward");
      motor.motorB("forward");
    }
  }
}
