#pragma once

#include <Arduino.h>

class motorController {
    int motor1A, motor1B, motor2A, motor2B;

  public:

    motorController(int motor1A, int motor1B, int motor2A, int motor2B) {
      this->motor1A = motor1A;
      this->motor1B = motor1B;
      this->motor2A = motor2A;
      this->motor2B = motor2B;

      pinMode(motor1A, OUTPUT);
      pinMode(motor1B, OUTPUT);
      pinMode(motor2A, OUTPUT);
      pinMode(motor2B, OUTPUT);
    }

    void motorSpinAForward() {
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
    }
    void motorSpinBForward() {
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
    }
    void motorSpinABackward() {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, HIGH);
    }
    void motorSpinBBackward() {
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, HIGH);
    }

    void motorSpinForward() {
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2B, LOW);
    }
    void motorSpinBackward() {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor1B, HIGH);
      digitalWrite(motor2B, HIGH);
    }

    void motorAStop() {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
    }
    void motorBStop() {
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
    }
    void motorStop() {
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
    }
};
