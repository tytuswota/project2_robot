int knop = 0;
int timer = 0;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), knopSwitch, FALLING);
}

void knopSwitch() {
  knop = !knop;
}

void loop() {
  alarm();
}

void alarm(){
  if (knop == 1) {
    for (int i = 0; i < 4; i++) {
      tone(7, 1000);
      digitalWrite(8, 1);
      digitalWrite(9, 0);
      delay(600);
      tone(7, 500);
      digitalWrite(8, 0);
      digitalWrite(9, 1);
      delay(600);
    }

    for (int i = 0; i < 10; i++) {
      tone(7, 1500);
      digitalWrite(8, 1);
      digitalWrite(9, 0);
      delay(50);
      tone(7, 500);
      digitalWrite(8, 0);
      digitalWrite(9, 1);
      delay(50);
    }

    noTone(7);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
  }
}
