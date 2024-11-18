#include <LiquidCrystal.h>
#include <Servo.h>  
#include <Arduino.h>
#define servoAngel 180
#define animation 15
#define delayTime 10
#define setCursorZero 0
#define setCursorOne 1


LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

Servo myservo;
int i = 0;
int angle = 0;  

void setup() {
  lcd_1.begin(16, 2);  
  // lcd_1.print("Control Servo");

  myservo.attach(10);  
}

void loop() {
  for (angle = 0; angle <= servoAngel; angle++) {
    myservo.write(angle);  
    lcd_1.setCursor(setCursorZero, setCursorOne);
    // lcd_1.print("Angle: ");
    // lcd_1.print(angle);  
    delay(delayTime);  
  }

  for (angle = servoAngel; angle >= 0; angle--) {
    myservo.write(angle);
    lcd_1.setCursor(setCursorZero, setCursorOne);
    // lcd_1.print("Angle: ");
    // lcd_1.print(angle);  // Afișează unghiul pe LCD
    delay(delayTime);
  }

  for (i = 0; i <= animation; i++) {
    delay(delayTime);
    lcd_1.setCursor(i, setCursorZero);
    lcd_1.write("*");
    lcd_1.setCursor(i, setCursorOne);
    lcd_1.print("*");
    delay(delayTime);
  }
  lcd_1.clear();

  for (i = 0; i <= animation; i++) {
    delay(delayTime); 
    lcd_1.setCursor(i, setCursorZero);
    lcd_1.write("->");
    lcd_1.setCursor(i, setCursorOne);
    lcd_1.print("->");
    delay(delayTime);
  }
  lcd_1.clear();

  for (i = animation; i >= 0; i--) {
    delay(delayTime); 
    lcd_1.setCursor(i, setCursorZero);
    lcd_1.write("<-");
    lcd_1.setCursor(i, setCursorOne);
    lcd_1.print("<-");
    delay(delayTime);
  }
  lcd_1.clear();

  for (i = animation; i >= 0; i--) {
    delay(delayTime);
    lcd_1.setCursor(i, setCursorZero);
    lcd_1.write("*");
    lcd_1.setCursor(i, setCursorOne);
    lcd_1.print("*");
    delay(delayTime);
  }
  lcd_1.clear();
}
