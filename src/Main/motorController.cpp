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

    void motorA(String command){
      if(command == "forward"){
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor1B, LOW);
      }
      else if(command == "backward"){
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, HIGH);
      }
      else if(command == "stop"){
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, LOW);
      }
      else{
        return null;
      }
    }

    void motorB(String command){
      if(command == "forward"){
        digitalWrite(motor2A, HIGH);
        digitalWrite(motor2B, LOW);
      }
      else if(command == "backward"){
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, HIGH);
      }
      else if(command == "stop"){
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, LOW);
      }
      else{
        return null;
      }
    }
};
