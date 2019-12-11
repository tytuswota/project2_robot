#define infraroodLinks 7
#define infraroodRechts 8

#define motorPin1A 3
#define motorPin1B 2
#define motorPin2A 5
#define motorPin2B 4

#include "motorController.cpp"

motorController motor(motorPin1A, motorPin1B, motorPin2A, motorPin2B);

void setup() {
  Serial.begin(9600);
  pinMode(infraroodLinks, INPUT_PULLUP);
  pinMode(infraroodRechts, INPUT_PULLUP);
}

void loop() {
  int infraroodLinksVal = digitalRead(infraroodLinks);
  int infraroodRechtsVal = digitalRead(infraroodRechts);

  motor.motorSpinAForward();
  motor.motorSpinBBackward();
  
  //motor.motorSpinForward();

  /*if(infraroodLinksVal == 1){
    motor.motorBStop();
  }

  if(infraroodRechtsVal == 1){
    motor.motorAStop();
  }*/
}
