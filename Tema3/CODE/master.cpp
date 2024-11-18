#include <LiquidCrystal.h>
#include <Servo.h>  
#include <Arduino.h>


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
  for (angle = 0; angle <= 180; angle++) {
    myservo.write(angle);  
    lcd_1.setCursor(0, 1);
    // lcd_1.print("Angle: ");
    // lcd_1.print(angle);  
    delay(15);  
  }

  for (angle = 180; angle >= 0; angle--) {
    myservo.write(angle);
    lcd_1.setCursor(0, 1);
    // lcd_1.print("Angle: ");
    // lcd_1.print(angle);  // Afișează unghiul pe LCD
    delay(15);
  }

  for (i = 0; i <= 15; i++) {
    delay(10);
    lcd_1.setCursor(i, 0);
    lcd_1.write("*");
    lcd_1.setCursor(i, 1);
    lcd_1.print("*");
    delay(10);
  }
  lcd_1.clear();

  for (i = 0; i <= 15; i++) {
    delay(10); 
    lcd_1.setCursor(i, 0);
    lcd_1.write("->");
    lcd_1.setCursor(i, 1);
    lcd_1.print("->");
    delay(10);
  }
  lcd_1.clear();

  for (i = 15; i >= 0; i--) {
    delay(10); 
    lcd_1.setCursor(i, 0);
    lcd_1.write("<-");
    lcd_1.setCursor(i, 1);
    lcd_1.print("<-");
    delay(10);
  }
  lcd_1.clear();

  for (i = 15; i >= 0; i--) {
    delay(10);
    lcd_1.setCursor(i, 0);
    lcd_1.write("*");
    lcd_1.setCursor(i, 1);
    lcd_1.print("*");
    delay(10);
  }
  lcd_1.clear();
}
