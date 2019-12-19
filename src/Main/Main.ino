#define infraroodLinks 8
#define infraroodRechts 7

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

unsigned long int prevMillis = millis();

int usVoorPrev = 0;
int usOnderPrev = 0;

void setup() {
  Serial.begin(9600);
  pinMode(infraroodLinks, INPUT_PULLUP);
  pinMode(infraroodRechts, INPUT_PULLUP);
  usOnder = new UltrasonicSensor(ultrasoonTrigOnder, ultrasoonEchoOnder, &pulseTimeOnder, isrOnder);
  usVoor = new UltrasonicSensor(ultrasoonTrigVoor, ultrasoonEchoVoor, &pulseTimeVoor, isrVoor);
  usVoor->pulse();
}

void loop() {
  int infraroodLinksVal = digitalRead(infraroodLinks);
  int infraroodRechtsVal = digitalRead(infraroodRechts);

  int usVoorVal = usVoor->getLastDistance();
  int usOnderVal = usOnder->getLastDistance();

  if (usVoorVal < 50 && millis() > prevMillis + 200 && (usVoorVal - usVoorPrev < 30 && usVoorVal - usVoorPrev > -30)) {
    int x = 0;
    while (x < 50) {
      //Serial.println("Ultrasoon Voor: " + (String)usVoorVal());
      motor.motorSpinABackward();
      motor.motorSpinBForward();
      x++;
    }
    prevMillis = millis();
  }
  else if (usOnderVal > 100 && millis() > prevMillis + 200 && (usOnderVal - usOnderPrev < 30 && usOnderVal - usOnderPrev > -30)) {
    while (usOnderVal > 100 ) {
      motor.motorStop();
      prevMillis = millis();
    }
  }
  else {
    if (infraroodLinksVal == 1 && infraroodRechtsVal != 1) {
      motor.motorSpinBBackward();
      motor.motorSpinAForward();
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal != 1) {
      motor.motorSpinABackward();
      motor.motorSpinBForward();
    }
    else if (infraroodRechtsVal == 1 && infraroodLinksVal == 1) {
      motor.motorStop();
    }
    else {
      motor.motorSpinForward();
      Serial.println("forward");
    }
  }

  //Zet ultrasoon waarde in de variable usOnderPrev zodat we de volgende loop rotatie de vorige waarde kunnen lezen.
  usOnderPrev = usOnderVal;
  usVoorPrev = usVoorVal;
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
