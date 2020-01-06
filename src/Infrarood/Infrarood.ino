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
UltrasonicSensor *usVoor, *usOnder;

volatile unsigned long pulseTimeVoor;
volatile unsigned long pulseTimeOnder;
<<<<<<< HEAD
/*public boolean manualControl = false;
public boolean manualForward = false;
public boolean manualRight = false;
public boolean manualLeft = false;
public boolean manualBack = false;*/
=======
boolean manualControl = false;
boolean manualForward = false;
boolean manualRight = false;
boolean manualLeft = false;
boolean manualBack = false;
>>>>>>> b17da5b93e0bb095a2c6210dae74ae7ae4534ca4

void setup() {
  Serial.begin(9600);
  pinMode(infraroodLinks, INPUT_PULLUP);
  pinMode(infraroodRechts, INPUT_PULLUP);
  usVoor = new UltrasonicSensor(ultrasoonTrigVoor, ultrasoonEchoVoor, &pulseTimeVoor, isrVoor);
  usOnder = new UltrasonicSensor(ultrasoonTrigOnder, ultrasoonEchoOnder, &pulseTimeOnder, isrOnder);
  usVoor->pulse();
}

void loop() {

  /*if (Serial.available() > 0)
    {
    int x = Serial.read();
    if(x == 5)
    {
    manualControl = true;
    Serial.println("manual active");
    }
    }*/

//  if (!manualControl)
  //{
    int infraroodLinksVal = digitalRead(infraroodLinks);
    int infraroodRechtsVal = digitalRead(infraroodRechts);
<<<<<<< HEAD

    Serial.println("Sensor voor: " + (String)usVoor->getLastDistance());
    if (usVoor->getLastDistance() < 40) {
      while (usVoor->getLastDistance() < 40) {
        motor.motorStop();
      }
    }

    Serial.println("Sensor onder: " + String(usOnder->getLastDistance()));
    if (usOnder->getLastDistance() > 40) {
=======
  
    Serial.println("Sensor voor: " + (String)usVoor->getLastDistance());
    if(usVoor->getLastDistance() < 40){
      while(usVoor->getLastDistance() < 40){
        motor.motorStop();
      }
    }
  
    Serial.println("Sensor onder: " + String(usOnder->getLastDistance()));
    if(usOnder->getLastDistance() > 40) {
>>>>>>> b17da5b93e0bb095a2c6210dae74ae7ae4534ca4
      Serial.println("Afgrond!");
    }

    if (infraroodLinksVal == 1 && infraroodRechtsVal != 1) {
      motor.motorBStop();
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal != 1) {
      motor.motorAStop();
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal == 1) {
      motor.motorStop();
    }
    else {
      motor.motorSpinForward();
    }
 /* } else
  {
    if (Serial.available() > 0)
    {
      int x = Serial.read();
      if (x == 1)
      {
        manualForward = true;
        manualBack = false;
        manualRight = false;
        manualLeft = false;
      } else if (x == 2)
      {
        manualBack = true;
        manualForward = false;
        manualRight = false;
        manualLeft = false;
      }
      else if (x == 3)
      {
        manualRight = true;
        manualLeft = false;
        manualBack = false;
        manualForward = false;
      }
      else if (x == 4)
      {
        manualLeft = true;
        manualRight = false;
        manualBack = false;
        manualForward = false;
      } else if (x == 5)
      {
        manualControl = false;
      }

      if (manualForward)
      {
        motor.motorSpinForward();
      } else if (manualBack)
      {
        motor.motorSpinBackward();
      } else if (manualRight)
      {
        motor.motorSpinAForward();
        motor.motorSpinBBackward();
      } else if (manualLeft)
      {
        motor.motorSpinBForward();
        motor.motorSpinABackward();
      }
    }*/


  }

void isrVoor() {
  static unsigned long int start;
  if (digitalRead(ultrasoonEchoVoor)) {
    start = micros();
  } else {
    pulseTimeVoor = micros() - start;
  }
  usOnder->pulse();
}

void isrOnder() {
  static unsigned long int start;
  if (digitalRead(ultrasoonEchoOnder)) {
    start = micros();
  } else {
    pulseTimeOnder = micros() - start;
  }
  usVoor->pulse();
}
