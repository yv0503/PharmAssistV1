#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

constexpr int redButtonPin = 2;
constexpr int blueButtonPin = 4;

int timeForRotateToNextContainer = 200; // calibration required
int redButtonState = 0;
int blueButtonState = 0;
int turnTimes = 0;
bool pressedState = false;

int centerAlign(const String &textToPrint) {
  const int centerPoint = (20 - textToPrint.length()) / 2;
  return centerPoint;
}

void lcdDisplayReset() {
  // clears text per row
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.clear();
}

void lcdChangeText(const String &string1, const String &string2, const String &string3, const String &string4) {
  lcdDisplayReset();
  lcd.setCursor(centerAlign(string1), 0);    // move cursor the first row and center align
  lcd.print(string1);                        // print message at the first row
  lcd.setCursor(centerAlign(string2), 1);    // move cursor to the second row and center align
  lcd.print(string2);                        // print message at the second row
  lcd.setCursor(centerAlign(string3), 2);    // move cursor to the third row and center align
  lcd.print(string3);                        // print message at the third row
  lcd.setCursor(centerAlign(string4), 3);    // move cursor to the fourth row and center align
  lcd.print(string4);                        // print message the fourth row
}

int servoTurn(int turnTimes, const int timeForRotateToNextContainer) {
    myServo.write(180);                  // starts servo clockwise
    delay(timeForRotateToNextContainer); // time required to rotate to next container
    myServo.write(90);                   // stops servo
    turnTimes++;                         // counts the amount of times the servo has changed container
      if (turnTimes > 4) {
        turnTimes = 0;                   // resets once it has done a full rotation
      }
    return turnTimes;
}

void servoReset(const int number, const int timeForRotateToNextContainer) {
    switch (number) {
      case 1:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed 1");
        myServo.write(180);
        delay(timeForRotateToNextContainer * 4);
        myServo.write(90);
        break;
      case 2:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed 2");
        myServo.write(180);
        delay(timeForRotateToNextContainer * 3);
        myServo.write(90);
        break;
      case 3:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed 3");
        myServo.write(180);
        delay(timeForRotateToNextContainer * 2);
        myServo.write(90);
        break;
      case 4:
        lcdChangeText("LCD ","Blue Button", "Has been", "Pressed 4");
        myServo.write(180);
        delay(timeForRotateToNextContainer);
        myServo.write(90);
        break;
      default: ;
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

  if (redButtonState == HIGH && pressedState == false) {
    lcdChangeText("LCD ","Red Button", "Has been", "Pressed");
    turnTimes = servoTurn(turnTimes, timeForRotateToNextContainer);
    pressedState = true;
  }

  if (blueButtonState == HIGH && pressedState == false) {
    servoReset(turnTimes, timeForRotateToNextContainer);
    turnTimes = 0;
    pressedState = true;
  }

  else if (blueButtonState == LOW && redButtonState == LOW && pressedState == true) {
    lcdChangeText("LCD ","Buttons", "are", "Available");
    pressedState = false;
  }


}

