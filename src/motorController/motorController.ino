#define motorPin1A 2
#define motorPin1B 3
#define motorPin2A 4
#define motorPin2B 5

void setup() {
  pinMode(motorPin1A, OUTPUT);
  pinMode(motorPin1B, OUTPUT);
  pinMode(motorPin2A, OUTPUT);
  pinMode(motorPin2B, OUTPUT);
}

void loop() {
  motorSpinAForward();
  motorSpinBForward();
}

void motorSpinAForward() {
  digitalWrite(motorPin1A, HIGH);
  digitalWrite(motorPin1B, LOW);
}
void motorSpinBForward() {
  digitalWrite(motorPin2A, HIGH);
  digitalWrite(motorPin2B, LOW);
}
void motorSpinABackward() {
  digitalWrite(motorPin1A, LOW);
  digitalWrite(motorPin1B, HIGH);
}
void motorSpinBBackward() {
  digitalWrite(motorPin2A, LOW);
  digitalWrite(motorPin2B, HIGH);
}

void motorAStop() {
  digitalWrite(motorPin1A, LOW);
  digitalWrite(motorPin1B, LOW);
}
void motorBStop() {
  digitalWrite(motorPin2A, LOW);
  digitalWrite(motorPin2B, LOW);
}
