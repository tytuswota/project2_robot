#pragma once

#include <Arduino.h>

class UltrasonicSensor {
  public:
  int trig, echo;

  UltrasonicSensor() {}
  
  UltrasonicSensor(const int trig, const int echo, void(*isr)(void)) {

    // check if the pin can be used for an interrupt
    if(!(echo == 2 || echo == 3)) {

      // just prints a message since there is no proper error handling
      Serial.println("UltrasonicSensor object made with non-interrupt pin");
    }

    // set up the rest
    this->trig = trig;
    this->echo = echo;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    attachInterrupt(digitalPinToInterrupt(echo), isr, CHANGE);
  }

  // this function sends a pulse to check the distance
  void pulse() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  }
};
