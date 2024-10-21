# Homework 1 - Electric Vehicle Charging System #

## Requirements ##

### 1.1 Description ###
In this assignment, you are required to simulate a charging station for an electric vehicle using multiple LEDs and buttons. In this task, you must consider the button states and use debouncing, as well as coordinate all components as in a real-life scenario.

### 1.2 Components ###
- 4x LEDs (to simulate the charging percentage)
- 1x RGB LED (for free or occupied state)
- 2x Buttons (for starting and stopping charging)
- 8x Resistors (6x 220/330 ohm, 2x 1K)
- Breadboard
- Jumper wires

### Model ###
![ModelTema1](Imagini/ModelTema1.png)

## [Tinkercad Model](https://www.tinkercad.com/things/2ggkFyA9x1r/editel?sharecode=5z0b_qXrEgzh6FHUe4yNIIN5D7Z4_BkADiV4FdSNRws) ##


## Images of the constructed circuit ##

<img src="Imagini/Tema1Poza1.jpg" width="685" alt="Tema1Poza1"/>
<img src="Imagini/Tema1Poza2.jpg" width="685" alt="Tema1Poza2"/>
<img src="Imagini/Tema1Poza3.jpg" width="685" alt="Tema1Poza3"/>
<img src="Imagini/Tema1Poza4.jpg" width="685" alt="Tema1Poza4"/>
<img src="Imagini/Tema1Poza5.jpg" width="685" alt="Tema1Poza5"/>


### 1.3 Technical Details ###
The RGB LED represents the availability of the station. If the station is free, the LED will be green, and if the station is occupied, it will turn red.

- The simple LEDs represent the battery charging level, which will be simulated through a progressive loader (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). The loader will charge by sequentially lighting the LEDs at a fixed interval of 3 seconds. The LED indicating the current charging percentage will blink, while the subsequent LEDs will be continuously lit, and the others will be off.

- A short press of the start button will begin charging. Pressing this button during charging will do nothing.

- A long press of the stop button will forcibly stop the charging and reset the station to the free state. Pressing this button while the station is free will do nothing.

### 1.4 Flow ###
The station's state is ‘free.’ The loader is off, and the availability LED is green.

The start button is pressed.

The availability LED turns red, and charging begins by lighting the first LED L1.

LED 1 blinks for 3 seconds, while the others remain off.

After completing the first charging percentage of 25%, the LED remains lit, and the next LED starts blinking.

At the end of the charging process, all LEDs will blink simultaneously three times and then turn off to signal the completion of the process.

The availability LED turns green.

If at any time from the start of charging to its completion the stop button is pressed for a long time (minimum 1 second), charging is interrupted with the end animation (all LEDs blink three times), and the availability LED turns green.

## Demo video of the functionality of the assignment ##

### Start ###
https://github.com/user-attachments/assets/2915d00b-8469-4a76-ab7a-41299e97a53a



### Stop ###
https://github.com/user-attachments/assets/dc9e0bfe-6175-4be8-a79b-d534cdce7977

# Explaining the code #



## Features
- Start charging with the START button.
- Stop charging by holding the STOP button for 1 second.
- Charging is indicated by blinking LEDs.
- After charging is complete, all LEDs will blink three times.

## Pin Configuration
- START_BUTTON_PIN: Pin number for the start button (pin 3).
- STOP_BUTTON_PIN: Pin number for the stop button (pin 2).
- RED_PIN: Pin number for the red LED (pin 6).
- GREEN_PIN: Pin number for the green LED (pin 5).
- BLUE_PIN: Pin number for the blue LED (pin 4).
- LED_PINS: Array containing pin numbers for the four charging LEDs (pins 7 to 10).

## Constants
- DEBOUNCE_DELAY: Delay for button debounce (50 milliseconds).
- LED_BLINK_INTERVAL: Interval for LED blinking (500 milliseconds).
- TOTAL_LEDS: Total number of charging LEDs (4).
- BLINKS_PER_LED: Number of blinks for each LED before moving to the next (3).

## Functions
- `void setup()`: Initializes pin modes and starts serial communication.
- `void loop()`: Main loop to read button states and manage the charging process.
- `void startCharging()`: Starts the charging process and initializes the first LED.
- `void handleChargingProcess()`: Manages the blinking sequence of the LEDs during charging.
- `void finishCharging()`: Handles the completion of charging and triggers a blink sequence.
- `void resetCharging()`: Resets the charging state and turns off all LEDs.
- `void blinkAllLeds()`: Blinks all LEDs together.

## Usage
1. Connect the components according to the pin configuration.
2. Upload the sketch to your Arduino.
3. Press the START button to begin the charging sequence.
4. Hold the STOP button for 1 second to stop the charging process.



