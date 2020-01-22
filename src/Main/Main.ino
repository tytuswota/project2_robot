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
#define motorPin2A 4
#define motorPin2B 5

#define hallSensor1 A0
#define hallSensor2 A1
#define hallSensor3 A2

#define magnetDetectionLed A3

#define usFrontDistance 150
#define usUnderDistance 300

constexpr bool debug = false;

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
void checkHallSensors(int hallSensorOutput);

motorController motor(motorPin1A, motorPin1B, motorPin2A, motorPin2B);
/*---------------------*/


/*------Main Code------*/
void setup() {
  Serial.begin(9600);
  pinMode(irLeft, INPUT_PULLUP);
  pinMode(irRight, INPUT_PULLUP);
  pinMode(hallSensor1, INPUT_PULLUP);
  pinMode(hallSensor2, INPUT_PULLUP);
  pinMode(hallSensor3, INPUT_PULLUP);
  pinMode(magnetDetectionLed, OUTPUT);
  usUnder = UltrasonicSensor(usTrigUnder, usEchoUnder, isrUnder);
  usFront = UltrasonicSensor(usTrigFront, usEchoFront, isrFront);
  startTimerInterruptLoop();
}

void loop() {
  getEspResponse();
  checkHallSensors(!(digitalRead(hallSensor1) && digitalRead(hallSensor2) && digitalRead(hallSensor3)));

  if (debug) Serial.println(manControl);

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
        motor.motorA("backward");
        motor.motorB("forward");
        if (debug) Serial.println("Left");
        break;
      default:
        motor.motorA("stop");
        motor.motorB("stop");
        if (debug) Serial.println("Stop");
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
      unsigned long prevTime = millis();
      motor.motorA("backward");
      motor.motorB("backward");
      while(prevTime + 500 > millis()){getEspResponse();}
      prevTime = millis(); 
      motor.motorA("backward");
      motor.motorB("forward");
      while(prevTime + 250 > millis()){getEspResponse();}
      prevTime = millis();
      motor.motorA("forward");
    }
    else if (timeToMillimeters(pulseTimeUnder) > usUnderDistance) {
      Serial.print(usUnderDistance);
      unsigned long prevTime = millis();
      while(prevTime + 2000 > millis()){
        motor.motorA("backward");
        motor.motorB("backward");
        if(debug) Serial.println("AFGROND");
      }
      prevTime = millis();
      while(prevTime + 1000 > millis()){
        motor.motorA("forward");
      }
      motor.motorB("forward");
    }
    else {
      if (irLeftVal == 1 && irRightVal != 1) {
        unsigned long prevTime = millis();
        motor.motorA("backward");
        motor.motorB("backward");
        while(prevTime + 500 > millis()){}
        prevTime = millis();
        motor.motorA("forward");
        while(prevTime + 500 > millis()){}
      } else if (irRightVal == 1 && irLeftVal != 1) {
        unsigned long prevTime = millis();
        motor.motorA("backward");
        motor.motorB("backward");
        while(prevTime + 500 > millis()){}
        motor.motorB("forward");
        prevTime = millis();
        while(prevTime + 500 > millis()){}
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
bool oneTime = false;
void getEspResponse() {
  int serialBuffer = 0;
  if (Serial.available() > 0) {
    espResponse = Serial.read();
  }

  if(espResponse == 5 && !oneTime){
    manControl = !manControl;
    oneTime = true;
  }
  else if(espResponse != 5 && oneTime){
    oneTime = false;
  }
  
  if (debug) Serial.println("ESP Response : " + (String)espResponse);
}
/*------------------------*/

/*--Hall sensor Functies--*/
void checkHallSensors(int hallSensorOutput) {
  static int ledTurnOffTime = 0;
  if(hallSensorOutput) {
    ledTurnOffTime = millis() + 2000;
    digitalWrite(magnetDetectionLed, 1);
  }
  if(millis() > ledTurnOffTime) {
    digitalWrite(magnetDetectionLed, 0);
  }
}
/*------------------------*/
