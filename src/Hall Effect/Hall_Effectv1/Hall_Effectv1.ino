#define ledPin  7
#define hallPin  2
#define piezoPin 5

int hallVall = 0;
int previousState = HIGH;





void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(hallPin, INPUT);
  //  attachInterrupt(2, hall_ISR, CHANGE);


}

void loop()
{

  hallSensor();

}

void hallSensor()
{
  hallVall = digitalRead(hallPin);
  if (hallVall == LOW && previousState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Detected");
    Alarm();

  }
  else
  {
    Serial.println("Nothing Detected");
    digitalWrite(ledPin, LOW);
  }
}

void Alarm()
{    
      for (int i = 0; i < 2; i++) 
      {
      tone(piezoPin, 1000);
      delay(600);
      tone(7, 500);
      delay(600);
      noTone(piezoPin);
      }

      for (int i = 0; i < 5; i++) 
      {
        tone(piezoPin, 1500);      
        delay(50);
        tone(piezoPin, 500);
        delay(50);
        noTone(piezoPin);
      }
}
