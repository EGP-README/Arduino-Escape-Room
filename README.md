# Arduino-Escape-Room
Arduino Sketches that control various sensors and actuators for a specific puzzle and hardware setup.

## C2 - Escape Solution Command and Control
- The C2 rotates a servo moter which releases an RFID key that "Deactivates" the Escape Room to complete the game
- Controls an LCD screen displaying the status of the Escape Room
- Controls a small buzzer that emits a short tone upon each riddle being solved
- Controls LEDs that light up with each riddle being solved

## Riddle 1
- Consists of a Tilt switch which was placed in a physical cylander and must be in the correct binary state for the riddle solve to trigger
- Includes four servo motors which rotate at the press of button switches; servos must be at right angle all at the same time to trigger win state
- Servo motors act as pointers to numbers on the riddle board. The riddle involes getting them to point to a specific code and having the cylinder int he right position at the same time

## Riddle 2
