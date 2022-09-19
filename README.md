# Arduino-Escape-Room
Arduino Sketches that control various sensors and actuators for a specific puzzle and hardware setup.

## C2 - Escape Solution Command and Control
- The C2 rotates a servo motor which releases an RFID key that "Deactivates" the Escape Room to complete the game
- Controls an LCD screen displaying the status of the Escape Room
- Controls a small buzzer that emits a short tone upon each riddle being solved
- Controls LEDs that light up with each riddle being solved
- The codes, and state of devices that trigger riddles to be solved are hard coded and easily adjusted to fit new riddle solutions

## Riddle 1
- Consists of a Tilt switch which was placed in a physical cylinder and must be in the correct binary state for the riddle to reach the solved state
- Includes four servo motors which rotate at the press of button switches; servos must be at right angle all at the same time to trigger win state
- Servo motors act as pointers to numbers on the riddle board. The riddle involves getting them to point to a specific combination and having the cylinder in the right position at the same time

## Riddle 2
- Consists of a spinning fan powered by a modulating motor, a water depth sensor, and a keypad for code entry
- To solve riddle two, the fan must be stopped by dipping the water depth sensor in a cup of water and the secret code must be entered

## Riddle 3
- Consists of a heat sensor and a light sensor
- To solve, the light sensor must be covered or the lights must be turned off to get below the specified darkness threshold and the heat sensor must be heated to around 45 degrees celsius which requires a lighter


![top_down](https://user-images.githubusercontent.com/103903501/188039209-b9b5151e-d310-44da-a239-7080942cd583.jpg)
![LCD_screen](https://user-images.githubusercontent.com/103903501/188039203-9a3f2b9a-2918-45a4-9ce0-ca8bbafb4479.jpg)
![riddle1](https://user-images.githubusercontent.com/103903501/188039205-083858fc-db15-45bf-87a2-f5ed5deb717f.jpg)
![riddle2](https://user-images.githubusercontent.com/103903501/188039206-f64fcb80-8d93-4f60-a272-284e3e7ebd6d.jpg)
![riddle2_2](https://user-images.githubusercontent.com/103903501/188039207-8dc3c94c-eb0b-427c-b29f-9d6044d78c76.jpg)
![heat_light_sensors](https://user-images.githubusercontent.com/103903501/188039201-00284e4e-b62e-481e-a2f3-2c95793a502b.jpg)

