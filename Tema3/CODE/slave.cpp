#include <LiquidCrystal.h>
#include <Servo.h>

#define redPinRGB_A0 2
#define bluePinRGB_A0 4
#define greenPinRGB_A0 3
#define red_A0 8
#define green_A0 9
#define blue_A0 10

#define redPinRGB_A1 5
#define bluePinRGB_A1 7
#define greenPinRGB_A1 6
#define red_A1 11
#define green_A1 12
#define blue_A1 13

#define startButton A2  

#define DEBOUNCE_DELAY 50

#define numbercolor 3
#define roundNumber 3
#define colorRed 0
#define colorGreen 1
#define colorBlue 2

#define reactionTimeMax 1000
#define pointsMax 10
#define reactionTimeMedium1 2000
#define pointsMedium1 7
#define reactionTimeMedium2 3000
#define pointsMedium2 5
#define pointsMin 1

int lastKeyVal_A0 = -1;
unsigned long lastDebounceTime_A0 = 0;
int currentColor_A0 = -1;
unsigned long colorChangeTime_A0 = 0;  
unsigned long reactionTime_A0 = 0;     
int score_A0 = 0;  
int totalScore_A0 = 0;  // Scor total acumulat pentru 3 runde

int lastKeyVal_A1 = -1;
unsigned long lastDebounceTime_A1 = 0;
int currentColor_A1 = -1;
unsigned long colorChangeTime_A1 = 0;  
unsigned long reactionTime_A1 = 0;     
int score_A1 = 0;  
int totalScore_A1 = 0;  // Scor total acumulat pentru 3 runde

int roundCounter = 0;  // Contor de runde
bool gameActive = false;  
unsigned long roundStartTime = 0;  
const unsigned long roundDuration = 30000;  

const int redThreshold_A0 = 685;
const int greenThreshold_A0 = 515;
const int blueThreshold_A0 = 1020;

const int redThreshold_A1 = 685;
const int greenThreshold_A1 = 515;
const int blueThreshold_A1 = 1020;

const int tolerance = 20;

void turnOffAllLEDs() {
  digitalWrite(red_A0, LOW);
  digitalWrite(green_A0, LOW);
  digitalWrite(blue_A0, LOW);
  digitalWrite(red_A1, LOW);
  digitalWrite(green_A1, LOW);
  digitalWrite(blue_A1, LOW);
  digitalWrite(redPinRGB_A0, LOW);
  digitalWrite(greenPinRGB_A0, LOW);
  digitalWrite(bluePinRGB_A0, LOW);
  digitalWrite(redPinRGB_A1, LOW);
  digitalWrite(greenPinRGB_A1, LOW);
  digitalWrite(bluePinRGB_A1, LOW);
}

void setRandomColor_A0() {
  int newColor;
  do {
    newColor = random(numbercolor);
  } while (newColor == currentColor_A0);

  currentColor_A0 = newColor;
  colorChangeTime_A0 = millis();  

  digitalWrite(redPinRGB_A0, newColor == colorRed);
  digitalWrite(greenPinRGB_A0, newColor == colorGreen);
  digitalWrite(bluePinRGB_A0, newColor == colorBlue);
}

void setRandomColor_A1() {
  int newColor;
  do {
    newColor = random(numbercolor);
  } while (newColor == currentColor_A1);

  currentColor_A1 = newColor;
  colorChangeTime_A1 = millis();  

  digitalWrite(redPinRGB_A1, newColor == colorRed);
  digitalWrite(greenPinRGB_A1, newColor == colorGreen);
  digitalWrite(bluePinRGB_A1, newColor == colorBlue);
}

bool checkStartButtonPress() {
  return digitalRead(startButton) == LOW;  
}

int calculatePoints(unsigned long reactionTime) {
  if (reactionTime < reactionTimeMax) {
    return pointsMax;  
  } else if (reactionTime < reactionTimeMedium1) {
    return pointsMedium1;  
  } else if (reactionTime < reactionTimeMedium2) {
    return pointsMedium2;   
  } else {
    return pointsMin;   
  }
}

void checkButtonAndSetLED_A0(int value) {
  if (!gameActive) return;  

  digitalWrite(red_A0, LOW);
  digitalWrite(green_A0, LOW);
  digitalWrite(blue_A0, LOW);

  if (abs(value - redThreshold_A0) < tolerance) {
    digitalWrite(red_A0, HIGH);
    if (currentColor_A0 == colorRed) {
      reactionTime_A0 = millis() - colorChangeTime_A0; 
      int points = calculatePoints(reactionTime_A0);
      score_A0 += points;  
      setRandomColor_A0();
      Serial.print("[A0] Puncte: ");
      Serial.println(points);
    }
  } else if (abs(value - greenThreshold_A0) < tolerance) {
    digitalWrite(green_A0, HIGH);
    if (currentColor_A0 == colorGreen) {
      reactionTime_A0 = millis() - colorChangeTime_A0;
      int points = calculatePoints(reactionTime_A0);
      score_A0 += points;
      setRandomColor_A0();
      Serial.print("[A0] Puncte: ");
      Serial.println(points);
    }
  } else if (abs(value - blueThreshold_A0) < tolerance) {
    digitalWrite(blue_A0, HIGH);
    if (currentColor_A0 == colorBlue) {
      reactionTime_A0 = millis() - colorChangeTime_A0;
      int points = calculatePoints(reactionTime_A0);
      score_A0 += points;
      setRandomColor_A0();
      Serial.print("[A0] Puncte: ");
      Serial.println(points);
    }
  }
}

void checkButtonAndSetLED_A1(int value) {
  if (!gameActive) return; 

  digitalWrite(red_A1, LOW);
  digitalWrite(green_A1, LOW);
  digitalWrite(blue_A1, LOW);

  if (abs(value - redThreshold_A1) < tolerance) {
    digitalWrite(red_A1, HIGH);
    if (currentColor_A1 == colorRed) {
      reactionTime_A1 = millis() - colorChangeTime_A1;
      int points = calculatePoints(reactionTime_A1);
      score_A1 += points;
      setRandomColor_A1();
      Serial.print("[A1] Puncte: ");
      Serial.println(points);
    }
  } else if (abs(value - greenThreshold_A1) < tolerance) {
    digitalWrite(green_A1, HIGH);
    if (currentColor_A1 == colorGreen) {
      reactionTime_A1 = millis() - colorChangeTime_A1;
      int points = calculatePoints(reactionTime_A1);
      score_A1 += points;
      setRandomColor_A1();
      Serial.print("[A1] Puncte: ");
      Serial.println(points);
    }
  } else if (abs(value - blueThreshold_A1) < tolerance) {
    digitalWrite(blue_A1, HIGH);
    if (currentColor_A1 == colorBlue) {
      reactionTime_A1 = millis() - colorChangeTime_A1;
      int points = calculatePoints(reactionTime_A1);
      score_A1 += points;
      setRandomColor_A1();
      Serial.print("[A1] Puncte: ");
      Serial.println(points);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(red_A0, OUTPUT);
  pinMode(green_A0, OUTPUT);
  pinMode(blue_A0, OUTPUT);
  pinMode(red_A1, OUTPUT);
  pinMode(green_A1, OUTPUT);
  pinMode(blue_A1, OUTPUT);
  pinMode(startButton, INPUT_PULLUP);  
  turnOffAllLEDs();
}

void loop() {
  if (!gameActive && checkStartButtonPress()) {
    gameActive = true;
    roundStartTime = millis();
    setRandomColor_A0();
    setRandomColor_A1();
    Serial.println("Jocul a început!");
  }

  if (gameActive) {
    int currentKeyVal_A0 = analogRead(A0);  
    int currentKeyVal_A1 = analogRead(A1);  

    checkButtonAndSetLED_A0(currentKeyVal_A0);
    checkButtonAndSetLED_A1(currentKeyVal_A1);

    if (millis() - roundStartTime > roundDuration) {
      Serial.println("Runda s-a terminat!");
      roundCounter++;
      
      totalScore_A0 += score_A0;
      totalScore_A1 += score_A1;
      
      Serial.print("[A0] Puncte runda: ");
      Serial.println(score_A0);
      Serial.print("[A1] Puncte runda: ");
      Serial.println(score_A1);
      Serial.print("[A0] Puncte totale: ");
      Serial.println(totalScore_A0);
      Serial.print("[A1] Puncte totale: ");
      Serial.println(totalScore_A1);

      if (roundCounter >= roundNumber) {
        Serial.println("S-a încheiat seria de 3 runde. Resetăm punctajele curente!");
        roundCounter = 0;
        totalScore_A0 = 0;  
        totalScore_A1 = 0;  
      }

      score_A0 = 0;
      score_A1 = 0;
      gameActive = false;
      turnOffAllLEDs();
    }
  }

  delay(100);  
 }
