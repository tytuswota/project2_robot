#include "PinMapping.h"

void setup() {
  pinMode(D1, OUTPUT);
}

void loop() {
  digitalWrite(D1, 0);
  delay(500);
  digitalWrite(D1, 1);
  delay(500);
}
