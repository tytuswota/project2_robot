/*
   Project 2 - RescueBots - Carier

   Namen: Don Luyendijk   - 0970101
          Tymek Pisko     - 0986216
          Gillbert Resida - 0990026
          Charlie de Raaf - 0987084

   Klas:  TI1E - Groep 4
*/

/*------Initialisatie------*/
#include "motorController.cpp"
#include "UltrasonicSensor.cpp"

#define irLeft 8
#define irRight 7

#define usTrigFront 11
#define usEchoFront 3
#define usTrigUnder 12
#define usEchoUnder 2

#define motorPin1A 10
#define motorPin1B 9
#define motorPin2A 5
#define motorPin2B 4

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
  usUnder = UltrasonicSensor(usTrigUnder, usEchoUnder, isrUnder);
  usFront = UltrasonicSensor(usTrigFront, usEchoFront, isrFront);
  startTimerInterruptLoop();
}

void loop() {
  getEspResponse();

  if (debug) Serial.println(manControl);

  if (manControl) {
    if (debug) Serial.println("ManControl");
    switch (espResponse) {
      case 1: //Forward
        motor.motorA("forward");
        motor.motorB("forward");
        if (debug) Serial.println("Forward");
        break;
      case 2: // Backward
        motor.motorA("backward");
        motor.motorB("backward");
        if (debug) Serial.println("Back");
        break;
      case 3: //Right
        motor.motorA("forward");
        motor.motorB("backward");
        if (debug) Serial.println("Right");
        break;
      case 4: //Left
        motor.motorA("backward");
        motor.motorB("forward");
        if (debug) Serial.println("Left");
        break;
      default: //If the button isn't pressed, stop both motors
        motor.motorA("stop");
        motor.motorB("stop");
        if (debug) Serial.println("Stop");
        break;
    }
  }
  else {
    if (debug) Serial.println("Normal mode");
    //Read ir values
    int irLeftVal = digitalRead(irLeft);
    int irRightVal = digitalRead(irRight);

    if (debug) Serial.println("IR Left : " + (String) irLeftVal);
    if (debug) Serial.println("IR Right : " + (String) irRightVal);

    if (debug) Serial.println("US Front : " + (String) timeToMillimeters(pulseTimeFront));
    if (debug) Serial.println("US Under : " + (String) timeToMillimeters(pulseTimeUnder));

    if (timeToMillimeters(pulseTimeFront) < usFrontDistance) { //Check the ultrasonic sensor on the front, if something is to close, execute the following code
      unsigned long prevTime = millis();
      motor.motorA("backward"); //Set both motors to backward
      motor.motorB("backward");
      while(prevTime + 500 > millis()){getEspResponse();} //Let the bot ride backward for 0.5 sec
      prevTime = millis(); 
      motor.motorB("forward"); //Set motors to left
      while(prevTime + 250 > millis()){getEspResponse();} //Let the bot turn for 0.25 sec
      prevTime = millis();
      motor.motorA("forward"); //Set both motors to forward
    }
    else if (timeToMillimeters(pulseTimeUnder) > usUnderDistance) { //Check the ultrasonic sensor on the bottom, if time between pulses is too big, execute the following code
      unsigned long prevTime = millis();
      motor.motorA("backward"); //Set both motors to backward
      motor.motorB("backward");
      while(prevTime + 2000 > millis()){getEspResponse();} //Let the bot ride backward for 2 sec
      prevTime = millis();
      motor.motorA("forward"); //Set motors to right
      while(prevTime + 1300 > millis()){getEspResponse();} //Let the bot turn for 1.3 sec
      motor.motorB("forward"); //Set both motors to forward
    }
    else {
      if (irLeftVal == 1 && irRightVal != 1) { //Check if the left ir sensor detects a line
        unsigned long prevTime = millis();
        motor.motorA("backward"); //Set both motors to backward
        motor.motorB("backward");
        while(prevTime + 500 > millis()){getEspResponse();} //Let the bot ride backward for 0.5 sec
        prevTime = millis();
        motor.motorA("forward"); //Set motors to right
        while(prevTime + 300 > millis()){getEspResponse();} //Let the bot ride backward for 0.3 sec
      } else if (irRightVal == 1 && irLeftVal != 1) { //Check if the right ir sensor detects a line
        unsigned long prevTime = millis();
        motor.motorA("backward"); //Set both motors to backward
        motor.motorB("backward");
        while(prevTime + 500 > millis()){getEspResponse();} //Let the bot ride backward for 0.5 sec
        motor.motorB("forward"); //Set motors to left
        prevTime = millis();
        while(prevTime + 300 > millis()){getEspResponse();} //Let the bot ride backward for 0.3 sec
      } else if (irLeftVal == 1 && irRightVal == 1) { //Check if both ir sensors detect a line
        unsigned long prevTime = millis();
        motor.motorA("backward"); //Set both motors to backward
        motor.motorB("backward");
        while(prevTime + 500 > millis()){getEspResponse();} //Let the bot ride backward for 0.5 sec
      } else { //If not a single sensor detects something, do this
        motor.motorA("forward"); //Set both motors to forward
        motor.motorB("forward");
      }
    }
  }
}
/*------------------------------*/


/*------us Functies------*/

// takes a pulse time in microseconds and returns the distance in millimeters
long timeToMillimeters(long pulseTime) {
  return ((pulseTime >> 1) / 2.9);
}

// start timer 1 at 10 Hz
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

// every time timer 1 triggers, send a trigger pulse to usFront
// when usFront sends a pulse back usUnder will be triggered to avoid interference
ISR(TIMER1_COMPA_vect) {
  usFront.pulse();
}

// handle response from usFront, this is attached as ISR to the echo pin
void isrFront() {
  static unsigned long start;

  // start counting if the pin goes high
  if (digitalRead(usFront.echo)) {
    start = micros();

  // stop counting if the pin goed low
  } else {
    pulseTimeFront = micros() - start;
  }
  usUnder.pulse(); // send pulse to usUnder
}

// handle response from usUnder, this is attached as ISR to the echo pin
void isrUnder() {
  static unsigned long start;

  // start counting if the pin goes high
  if (digitalRead(usUnder.echo)) {
    start = micros();

  // stop counting if the pin goes low
  } else {
    pulseTimeUnder = micros() - start;
  }
}
/*------------------------*/


/*------ESP Functies------*/
bool oneTime = false;
void getEspResponse() {
  int serialBuffer = 0;
  if (Serial.available() > 0) { //If the ESP sends data, read it
    espResponse = Serial.read();
  }

  if(espResponse == 5 && !oneTime){ //If the ESP sends the number 5, switch the bot mode, from manual to automatic and vice versa, after lock the switch so it can only switch once
    manControl = !manControl;
    oneTime = true;
  }
  else if(espResponse != 5 && oneTime){ //If the ESP sends anything else than the number 5, unlock the switch
    oneTime = false;
  }
  
  if (debug) Serial.println("ESP Response : " + (String)espResponse);
}
/*------------------------*/
