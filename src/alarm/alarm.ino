int knop = 0;
int timer = 0;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(5, INPUT_PULLUP);
 // attachInterrupt(digitalPinToInterrupt(5), knopSwitch, FALLING);
}

/*void knopSwitch() {
  knop = !knop;
}*/

void loop() {
  alarm();
}

void alarm(){
  //if (knop == 0) {
    for (int i = 0; i < 4; i++) {
      tone(6, 1000);
      analogWrite(A1, 255);
      analogWrite(A2, 0);
      delay(600);
      tone(6, 500);
      analogWrite(A1, 0);
      analogWrite(A2, 255);
      delay(600);
    }

    for (int i = 0; i < 10; i++) {
      tone(6, 1500);
      analogWrite(A1, 255);
      analogWrite(A2, 0);
      delay(50);
      tone(6, 500);
      analogWrite(A1, 0);
      analogWrite(A2, 255);
      delay(50);
    }

    noTone(6);
    analogWrite(A1, 0);
    analogWrite(A2, 0);
  //}
}
