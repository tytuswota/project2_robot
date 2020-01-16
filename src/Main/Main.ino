/*
   Project 2 - RescueBots

   Namen: Don Luyendijk   - 0970101
          Tymek Pisko     - 0986216
          Gillbert Resida - 0990026
          Charlie de Raaf - 0987084

   Klas:  TI1E - Groep 4
*/

/*------Initialisatie------*/
#include "motorController.cpp"
#include "UltrasonicSensor.cpp"

#define irLeft 7
#define irRight 8

#define usTrigFront 11
#define usEchoFront 2
#define usTrigUnder 12
#define usEchoUnder 3

#define motorPin1A 10
#define motorPin1B 9
#define motorPin2A 5
#define motorPin2B 4

#define usFrontDistance 150
#define usUnderDistance 300

bool debug = true;

int espResponse = 0;
int serialBuffer = 0;
boolean manControl = false;

UltrasonicSensor usFront, usUnder;
volatile unsigned long pulseTimeFront;
volatile unsigned long pulseTimeUnder;

long timeToMillimeters(long pulseTime);
void startTimerInterruptLoop();
ISR(TIMER1_COMPA_vect);
void isrFront();
void isrUnder();
void getEspResponse();

motorController motor(motorPin1A, motorPin1B, motorPin2A, motorPin2B);
/*---------------------*/


/*------Main Code------*/
void setup() {
  Serial.begin(9600);
  pinMode(irLeft, INPUT_PULLUP);
  pinMode(irRight, INPUT_PULLUP);
  usUnder = UltrasonicSensor(usTrigUnder, usEchoUnder, isrUnder);
  usFront = UltrasonicSensor(usTrigFront, usEchoFront, isrFront);
  startTimerInterruptLoop();
}

void loop() {
  getEspResponse();

  if (manControl) {
    if (debug) Serial.println("ManControl");
    switch (espResponse) {
      case 1:
        motor.motorA("forward");
        motor.motorB("forward");
        if (debug) Serial.println("Forward");
        break;
      case 2:
        motor.motorA("backward");
        motor.motorB("backward");
        if (debug) Serial.println("Back");
        break;
      case 3:
        motor.motorA("forward");
        motor.motorB("backward");
        if (debug) Serial.println("Right");
        break;
      case 4:
        motor.motorB("backward");
        motor.motorA("forward");
        if (debug) Serial.println("Left");
        break;
      case 5:
        manControl = !manControl;
        break;
    }
  }
  else {
    if (debug) Serial.println("Normal mode");
    int irLeftVal = digitalRead(irLeft);
    int irRightVal = digitalRead(irRight);

    if (debug) Serial.println("IR Left : " + (String) irLeftVal);
    if (debug) Serial.println("IR Right : " + (String) irRightVal);

    if (debug) Serial.println("US Front : " + (String) timeToMillimeters(pulseTimeFront));
    if (debug) Serial.println("US Under : " + (String) timeToMillimeters(pulseTimeUnder));

    if (timeToMillimeters(pulseTimeFront) < usFrontDistance) {
      while (timeToMillimeters(pulseTimeFront) < usFrontDistance) {
        motor.motorA("backward");
        motor.motorB("forward");
        getEspResponse();
        if (debug) Serial.println("US Front : " + (String)timeToMillimeters(pulseTimeFront));
      }
      motor.motorA("forward");
    }
    else if (timeToMillimeters(pulseTimeUnder) > usUnderDistance) {
      while (timeToMillimeters(pulseTimeUnder) > usUnderDistance) {
        motor.motorA("stop");
        motor.motorB("stop");
        getEspResponse();
        if (debug) Serial.println("US Under : " + (String)timeToMillimeters(pulseTimeUnder));
      }
    }
    else {
      if (irLeftVal == 1 && irRightVal != 1) {
        motor.motorB("stop");
        motor.motorA("forward");
      } else if (irRightVal == 1 && irLeftVal != 1) {
        motor.motorA("stop");
        motor.motorB("forward");
      } else if (irLeftVal == 1 && irRightVal == 1) {
        for (int i = 0; i < 500; i++) {
          motor.motorA("backward");
          motor.motorB("backward");
        }
      } else {
        motor.motorA("forward");
        motor.motorB("forward");
      }
    }
  }
}
/*------------------------------*/


/*------us Functies------*/
long timeToMillimeters(long pulseTime) {
  return ((pulseTime >> 1) / 2.9);
}

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
  usFront.pulse();
}

void isrFront() {
  static unsigned long start;
  if (digitalRead(usFront.echo)) {
    start = micros();
  } else {
    pulseTimeFront = micros() - start;
  }
  usUnder.pulse();
}

void isrUnder() {
  static unsigned long start;
  if (digitalRead(usUnder.echo)) {
    start = micros();
  } else {
    pulseTimeUnder = micros() - start;
  }
}
/*------------------------*/


/*------ESP Functies------*/
void getEspResponse() {
  int serialBuffer = 0;
  if (Serial.available() > 0) {
    espResponse = Serial.read();
  }
  if (debug) Serial.println("ESP Response : " + (String)espResponse);
}
/*------------------------*/
