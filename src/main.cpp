#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

constexpr int redButtonPin = 2;
constexpr int blueButtonPin = 4;

int redButtonState = 0;
int blueButtonState = 0;
int turnTimes = 0;
bool stateMachine = false;

int middleAlign(const String &textToPrint) {
  int centerPoint = (20 - textToPrint.length()) / 2;
  return centerPoint;
}

void lcdChangeText(const String &string1, const String &string2, const String &string3, const String &string4) {

    lcd.setCursor(middleAlign(string1), 0);    // move cursor the first row
    lcd.print(string1);   // print message at the first row
    lcd.setCursor(middleAlign(string2), 1);    // move cursor to the second row
    lcd.print(string2);   // print message at the second row
    lcd.setCursor(middleAlign(string3), 2);    // move cursor to the third row
    lcd.print(string3);   // print message at the third row
    lcd.setCursor(middleAlign(string4), 3);    // move cursor to the fourth row
    lcd.print(string4);   // print message the fourth row
}

void lcdDisplayReset() {
  lcd.setCursor(0, 0);    // move cursor the first row
  lcd.clear();   // print message at the first row
  lcd.setCursor(0, 1);    // move cursor to the second row
  lcd.clear();   // print message at the second row
  lcd.setCursor(0, 2);    // move cursor to the third row
  lcd.clear();   // print message at the third row
  lcd.setCursor(0, 3);    // move cursor to the fourth row
  lcd.clear();   // print message the fourth row
}

int servoTurn(int number) {
    myServo.write(180);
    delay(200);
    myServo.write(90);
    number++;
      if (number > 4) {
        number = 0;
      }
    return number;
}

void servoReset(int number) {
    switch (number) {
      case 1:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed1");
        myServo.write(180);
        delay(1000);
        myServo.write(90);
        break;
      case 2:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed2");
        myServo.write(180);
        delay(800);
        myServo.write(90);
        break;
      case 3:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed3");
        myServo.write(180);
        delay(600);
        myServo.write(90);
        break;
      case 4:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed4");
        myServo.write(180);
        delay(400);
        myServo.write(90);
        break;
      case 5:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed5");
        myServo.write(180);
        delay(200);
        myServo.write(90);
    }
}

void setup() {
  pinMode(redButtonPin, INPUT);
  pinMode(blueButtonPin, INPUT);
  lcd.init();
  lcd.backlight();
  myServo.attach(9);
}

void loop() {
  redButtonState = digitalRead(redButtonPin);
  blueButtonState = digitalRead(blueButtonPin);

  if (redButtonState == HIGH && stateMachine == false) {
    lcdChangeText("LCD ","Red Button", "Has been", "Pressed");
    turnTimes = servoTurn(turnTimes);
    stateMachine = true;
    delay(500);
  }

  if (blueButtonState == HIGH && stateMachine == false) {
    servoReset(turnTimes);
    turnTimes = 0;
    stateMachine = true;
  }

  else if (blueButtonState == LOW && redButtonState == LOW && stateMachine == true) {
    lcdDisplayReset();
    lcdChangeText("LCD ","Buttons", "are", "Available");
    stateMachine = false;
  }


}

