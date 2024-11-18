# Reflex Game for Two Players

## Task Description
This project involves creating a competitive reflex game for two players, testing their reaction speeds across multiple rounds. Each player has their own buttons and LEDs, and the goal is to press the button matching the color displayed on their RGB LED as quickly as possible. Scores are displayed on an LCD screen and updated throughout the game. At the end, the player with the highest score is declared the winner.

## Components Used
- **6x LEDs**: Two groups of 3 LEDs each, with different colors in each group.
- **2x RGB LEDs**: One for each player.
- **6x Buttons**: Three for each player.
- **1x LCD Screen**
- **1x Servomotor**
- **2x Breadboards**
- **Connecting Wires**
- **2x Arduino Uno Boards**

## Functionality
### Initialization
- The game starts with a welcome message displayed on the LCD.
- A button press starts the game. Options for the start button:
  - Any button starts the game.
  - A specific button designated as the start button.
  - A dedicated 7th button for starting the game.

### Game Rounds
- Each player has three buttons corresponding to three LED colors and one RGB LED.
- During a round:
  - The active player's RGB LED lights up in a color.
  - The player must press the button matching the color as quickly as possible to earn points. Faster responses yield more points.
  - Scores are updated on the LCD after each round.

### Game Timer
- A servomotor rotates during the game to indicate progress. A full rotation marks the end of the game.
- At the end:
  - The LCD displays the winner's name and final score for a few seconds before resetting to the welcome screen.

### Bonus Features
- Optional features:
  - Animations on the LCD or LEDs.
  - A buzzer for feedback and sound effects.
  - Player name input via buttons, joystick, or USART.

## Technical Details
### Communication
- Two Arduino Uno boards are used:
  - **Master Arduino**: Manages the LCD, servomotor, and game state (scores, active LEDs, etc.).
  - **Slave Arduino**: Handles buttons and LEDs, receiving instructions from the master and sending back button press data via SPI.

### Buttons
- Options for the start button include:
  - Any button.
  - A specific button marked on the breadboard.
  - A dedicated 7th button.
- During gameplay:
  - Buttons are used exclusively for game control.
  - Only the active player's buttons can control the game.
- Button multiplexing with resistors may be required due to limited GPIO pins.

### LEDs
- Each button corresponds to an LED of a specific color.
- RGB LEDs:
  - Light up in one of three colors corresponding to the buttons.
  - Remain off when it is not the player's turn.

### LCD
- Controlled using the `LiquidCrystal` library.
- Displays both players' scores throughout the game.
- Uses pins D4-D7 for data lines.

### Servomotor
- Starts at 0 degrees and rotates counterclockwise to indicate time progression.
- Use absolute rotation commands with the `Servo.h` library.

## Bonus
- Up to 1 extra point for features such as:
  - LED or LCD animations.
  - A buzzer for signaling events.
  - Allowing players to input their names via buttons, joystick, or USART.

## Notes
- Divide the code into multiple files (`.h/.hpp` and `.c/.cpp`) for better team collaboration.
- Pins A0-A6 can also be used as digital pins if necessary, even after button multiplexing.

