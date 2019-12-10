#pragma once

#include <Arduino.h>

class UltrasonicSensor {
  int trigPin, echoPin;
  unsigned long *pulseTime;

  public:

  UltrasonicSensor(int trigPin, int echoPin, unsigned long *pulseTime, void(*isr)(void)) {
    if(!(echoPin == 2 || echoPin == 3)) {
      // not an interrupt pin in this case, error handling?
    }
    attachInterrupt(digitalPinToInterrupt(echoPin), isr, CHANGE);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->pulseTime = pulseTime;
  }

  void pulse() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }

  int getLastDistance() {
    return ((*pulseTime >> 2) / 2.9);
  }
};
