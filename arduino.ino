#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int DISTANCE_LIMIT = 20;
int option = 1;

int triggerPin1 = 9;
int triggerPin2 = 11;
int echoPin1 = 8;
int echoPin2 = 10;

int redPin = 12;
int greenPin = 13;

// Smart Parking System Source Code

float getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);
  float duration = pulseIn(echoPin, HIGH);

  // Returning calculated distance.
  return (duration * 0.034) / 2;
}


void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  Serial.begin (9600);
  pinMode(triggerPin1, OUTPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void lcdScreenPrint() {
  float d1 = getDistance(triggerPin1, echoPin1);
  float d2 = getDistance(triggerPin2, echoPin2);
  
  Serial.println(String(d1));
  Serial.println(String(d2)); 
  
  if (d1 > DISTANCE_LIMIT & d2 > DISTANCE_LIMIT)
  {
    if (option != 1) {
      lcd.clear();
      option = 1;
      lcd.setCursor(0, 0);
      lcd.print("2 Slots Free");
      lcd.setCursor(0, 1);
      lcd.print("Slot 1 2 Free");
      delay(500);
    }
  }
  else if (d1 > DISTANCE_LIMIT && d2 <= DISTANCE_LIMIT)
  {
    if (option != 2) {
      lcd.clear();
      option = 2;
      lcd.setCursor(0, 0);
      lcd.print("1 Slot Free");
      lcd.setCursor(0, 1);
      lcd.print("Slot 1 Free");
      delay(500);
    }
  }
  else if (d1 <= DISTANCE_LIMIT && d2 > DISTANCE_LIMIT)
  {
    if (option != 3) {
      lcd.clear();
      option = 3;
      lcd.setCursor(0, 0);
      lcd.print("1 Slot Free");
      lcd.setCursor(0, 1);
      lcd.print("Slot 2 Free");
      delay(500);
    }
  }
  else
  {
    if (option != 4) {
      lcd.clear();
      option = 4;
      lcd.setCursor(0, 0);
      lcd.print("0 Slots Free");
      lcd.setCursor(0, 1);
      lcd.print("No Parking");
      delay(500);
    }
  }
}

void ledIndicator() {
  if (option < 4) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}

void loop()
{
  lcdScreenPrint();
  ledIndicator();
  delay(100);
}
