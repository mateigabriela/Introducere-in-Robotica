#include <Arduino.h>

const int START_BUTTON_PIN = 3;
const int STOP_BUTTON_PIN = 2;

const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 4;

const int LED_PINS[] = {7, 8, 9, 10};

const unsigned long DEBOUNCE_DELAY = 50;
const unsigned long LED_BLINK_INTERVAL = 500;
const int TOTAL_LEDS = 4;
const int BLINKS_PER_LED = 3;

unsigned long lastDebounceTime = 0;
int currentLed = 0;
bool isCharging = false;

void resetCharging();
void startCharging();
void handleChargingProcess();
void finishCharging();
void blinkAllLeds();

unsigned long buttonPressTime = 0;
bool buttonPressed = false;

void setup() {
    pinMode(START_BUTTON_PIN, INPUT_PULLUP);
    pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
    
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    for (int i = 0; i < TOTAL_LEDS; i++) {
        pinMode(LED_PINS[i], OUTPUT);
    }

    resetCharging();
    Serial.begin(9600);
    Serial.println("Arduino is starting up...");
}

void loop() {
    int startButtonState = digitalRead(START_BUTTON_PIN);
    int stopButtonState = digitalRead(STOP_BUTTON_PIN);
  
    if (startButtonState == LOW && (millis() - lastDebounceTime > DEBOUNCE_DELAY) && !isCharging) {
        Serial.println("Button pressed!");
        startCharging();
        lastDebounceTime = millis();
    }
   
    if (isCharging) {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        handleChargingProcess();
        
        if (stopButtonState == LOW && !buttonPressed) {
            buttonPressTime = millis();
            buttonPressed = true;
        } else if (stopButtonState == HIGH && buttonPressed) {
            buttonPressed = false;
        }

        if (buttonPressed && (millis() - buttonPressTime >= 1000)) {
            finishCharging();
            buttonPressed = false;
        }
    }
}

void startCharging() {
    isCharging = true;
    currentLed = 0;
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    Serial.println("Charging started...");
}

void handleChargingProcess() {
    static unsigned long ledStartTime = 0;
    static bool isLedOn = false;
    static int ledBlinkCount = 0;

    if (currentLed < TOTAL_LEDS) {
        unsigned long currentMillis = millis();
        
        if (ledBlinkCount == 0 && !isLedOn) {
            ledStartTime = currentMillis;
            isLedOn = true;
            digitalWrite(LED_PINS[currentLed], HIGH);
        }

        if (currentMillis - ledStartTime >= LED_BLINK_INTERVAL) {
            ledStartTime = currentMillis;
            isLedOn = !isLedOn;
            digitalWrite(LED_PINS[currentLed], isLedOn ? HIGH : LOW);

            if (!isLedOn) {
                ledBlinkCount++;
            }
        }

        if (ledBlinkCount >= BLINKS_PER_LED) {
            digitalWrite(LED_PINS[currentLed], HIGH);
            currentLed++;
            ledBlinkCount = 0;
        }
    } else {
        for (int i = 0; i < TOTAL_LEDS; i++) {
            digitalWrite(LED_PINS[i], LOW);
        }
        delay(500);
        finishCharging();
    }
}

void finishCharging() {
    for (int i = 0; i < 3; i++) {
        blinkAllLeds();
    }
    resetCharging();
}

void resetCharging() {
    isCharging = false;
    for (int i = 0; i < TOTAL_LEDS; i++) {
        digitalWrite(LED_PINS[i], LOW);
    }
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
}

void blinkAllLeds() {
    for (int i = 0; i < TOTAL_LEDS; i++) {
        digitalWrite(LED_PINS[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < TOTAL_LEDS; i++) {
        digitalWrite(LED_PINS[i], LOW);
    }
    delay(500);
}
