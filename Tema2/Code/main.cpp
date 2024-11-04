#include <Arduino.h>

// LED RGB pins
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;

// Button pins
const int startStopButtonPin = 2;
const int difficultyButtonPin = 3;

// Game state variables
volatile bool gameRunning = false;
volatile bool buttonPressed = false;
volatile bool difficultyButtonPressed = false;
unsigned long roundStartTime = 0;
unsigned long currentWordTime = 0;
int correctWordsCount = 0;
const int roundDuration = 30000;
const int zero = 0;

// Debouncing and difficulty change
unsigned long lastDifficultyChangeTime = 0;
const unsigned long debounceInterval = 300;

// Difficulty levels
enum Difficulty { EASY, MEDIUM, HARD };
Difficulty currentDifficulty = MEDIUM;
unsigned long wordDisplayInterval = 4000;

// Word dictionary
const char* words[] = {
  "arduino", "robot", "code", "led", "sensor", "button", "computer", "programming", "microcontroller", "display",
  "keyboard", "mouse", "monitor", "circuit", "resistor", "capacitor", "transistor", "breadboard", "voltage", "current",
  "resistance", "power", "frequency", "oscillator", "amplifier", "diode", "inductor", "relay", "switch", "battery"
};
const int wordsCount = sizeof(words) / sizeof(words[0]);
String currentWord = "";
bool newWordGenerated = false;
String inputWord = "";

// LED RGB functions
void setLEDColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Get a random word
String getRandomWord() {
  return words[random(0, wordsCount)];
}

// Start a new round
void startRound() {
  gameRunning = true;
  roundStartTime = millis();
  correctWordsCount = 0;
  newWordGenerated = false;

  switch (currentDifficulty) {
    case EASY:
      wordDisplayInterval = 6000;
      break;
    case MEDIUM:
      wordDisplayInterval = 4000;
      break;
    case HARD:
      wordDisplayInterval = 2000;
      break;
  }

  for (int i = 3; i > 0; i--) {
    setLEDColor(255, 255, 255);
    delay(500);
    setLEDColor(0, 0, 0);
    delay(500);
    Serial.println(i);
  }

  Serial.println("The round has started!");
  setLEDColor(0, 255, 0);
  
  currentWord = getRandomWord();
  Serial.print("Word: ");
  Serial.println(currentWord);
  currentWordTime = millis();
  newWordGenerated = true;
}

// Stop the round
void stopRound() {
  gameRunning = false;
  setLEDColor(255, 255, 255);
  Serial.print("\nThe round has ended! Correct words: ");
  Serial.println(correctWordsCount);
}

// Change difficulty
void changeDifficulty() {
  if (gameRunning) return;

  currentDifficulty = static_cast<Difficulty>((currentDifficulty + 1) % 3);

  switch (currentDifficulty) {
    case EASY:
      wordDisplayInterval = 6000;
      Serial.println("Easy mode on!");
      break;
    case MEDIUM:
      wordDisplayInterval = 4000;
      Serial.println("Medium mode on!");
      break;
    case HARD:
      wordDisplayInterval = 2000;
      Serial.println("Hard mode on!");
      break;
  }
}

// Check if the input word is correct
bool isWordCorrect(const String& inputWord) {
  return inputWord.equals(currentWord);
}

// ISR for Start/Stop button
void startStopISR() {
  if (millis() - lastDifficultyChangeTime > debounceInterval) {
    buttonPressed = true;
    lastDifficultyChangeTime = millis();
  }
}

// ISR for Difficulty button
void difficultyISR() {
  if (millis() - lastDifficultyChangeTime > debounceInterval) {
    difficultyButtonPressed = true;
    lastDifficultyChangeTime = millis();
  }
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(difficultyButtonPin, INPUT_PULLUP);

  Serial.begin(9600);

  setLEDColor(255, 255, 255);
  
  Serial.print("\nWelcome to the Typing Game! Press the Start/Stop button to begin.\n");

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(startStopButtonPin), startStopISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(difficultyButtonPin), difficultyISR, FALLING);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;
    if (!gameRunning) {
      startRound();
    } else {
      stopRound();
    }
  }

  if (difficultyButtonPressed) {
    difficultyButtonPressed = false;
    changeDifficulty();
  }

  if (gameRunning) {
    if ((millis() - roundStartTime) > roundDuration) {
      stopRound();
    } else {
      if (millis() - currentWordTime > wordDisplayInterval) {
        currentWord = getRandomWord();
        Serial.print("\nWord: ");
        Serial.println(currentWord);
        currentWordTime = millis();
        setLEDColor(0, 255, 0);
        inputWord = "";
      }

      while (Serial.available() > zero) {
        char c = Serial.read();
        if (c == '\b') {
          if (inputWord.length() > zero) {
            inputWord.remove(inputWord.length() - 1);
            Serial.print("\b \b");
          }
        } else if (c != '\r' && c != '\n') {
          inputWord += c;
          Serial.print(c);

          if ((inputWord.length() <= currentWord.length() && inputWord != currentWord.substring(0, inputWord.length())) || inputWord.length() > currentWord.length()) {
            setLEDColor(255, 0, 0);
          } else {
            setLEDColor(0, 255, 0);
          }

          if (isWordCorrect(inputWord)) {
            correctWordsCount++;
            Serial.println("\nCorrect Word!");
            setLEDColor(0, 255, 0);
            
            currentWord = getRandomWord();
            Serial.print("\nWord: ");
            Serial.println(currentWord);
            currentWordTime = millis();
            inputWord = "";
          }
        }
      }
    }
  }
}
