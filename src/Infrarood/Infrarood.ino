#define infraroodLinks 7
#define infraroodRechts 8

#define ultrasoonTrigVoor 11
#define ultrasoonEchoVoor 2
#define ultrasoonTrigOnder 12
#define ultrasoonEchoOnder 3

#define motorPin1A 9
#define motorPin1B 10
#define motorPin2A 5
#define motorPin2B 4

#include "motorController.cpp"
#include "UltrasonicSensor.cpp"

motorController motor(motorPin1A, motorPin1B, motorPin2A, motorPin2B);
UltrasonicSensor *usVoor;

volatile unsigned long pulseTimeVoor;

void setup() {
  Serial.begin(9600);
  pinMode(infraroodLinks, INPUT_PULLUP);
  pinMode(infraroodRechts, INPUT_PULLUP);
  usVoor = new UltrasonicSensor(ultrasoonTrigVoor, ultrasoonEchoVoor, &pulseTimeVoor, isrVoor);
  usVoor->pulse();
}

void loop() {
  int infraroodLinksVal = digitalRead(infraroodLinks);
  int infraroodRechtsVal = digitalRead(infraroodRechts);

  if(usVoor->getLastDistance() < 40){
    while(usVoor->getLastDistance() < 40){
      motor.motorStop();
      Serial.println(usVoor->getLastDistance());
    }
  }

  if(infraroodLinksVal == 1 && infraroodRechtsVal != 1){
    motor.motorBStop();
  }
  else if(infraroodRechtsVal == 1 && infraroodLinksVal != 1){
    motor.motorAStop();
  }
  else if(infraroodRechtsVal == 1 && infraroodLinksVal == 1){
    motor.motorStop();
  }
  else{
    motor.motorSpinForward();
  }
}

void isrVoor() {
  static unsigned long int start;
  if(digitalRead(ultrasoonEchoVoor)) {
    start = micros();
  } else {
    pulseTimeVoor = micros()-start;
  }
  usVoor->pulse();
}
