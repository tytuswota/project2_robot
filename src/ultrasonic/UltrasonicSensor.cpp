#pragma once

#include <Arduino.h>

class Ultrasonic {
  public:
  int trig, echo;

  Ultrasonic() {}
  
  Ultrasonic(const int trig, const int echo, void(*isr)(void)) {
    if(!(echo == 2 || echo == 3)) {
      Serial.println("UltrasonicSensor object made with non-interrupt pin");
    }
    this->trig = trig;
    this->echo = echo;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    attachInterrupt(digitalPinToInterrupt(echo), isr, CHANGE);
  }

  void pulse() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  }
};
