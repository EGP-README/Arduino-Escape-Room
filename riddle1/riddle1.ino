
#include <Servo.h>

/*
  @author: Evan Plumley

  @description Riddle 1 is is comprised of 4 servo motros that rotate at the press of a button.
  The servos rotate a fixed amount and thier position in degrees indicates whether they
  are in the correct position for the puzzle solution. The tilt switch must also be in the 
  correct position to indicate a puzzle solve state. 
*/

//Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4; 

int servoState1 = 160;
int servoState2 = 160;
int servoState3 = 160;
int servoState4 = 160;

//assign pin numbers to buttons
int button1 = 53; //riddle hand 4
int button2 = 51; //riddle hand 2
int button3 = 49; //riddle hand 1
int button4 = 47; //riddle hand 3

int servoDelay = 300;

int tiltSwitch = 13;
int winPin = 52;

void setup() {

  //set win pin
  pinMode(winPin, OUTPUT);
  digitalWrite(winPin, HIGH);

  //Setup button inputs
  pinMode(button1, INPUT_PULLUP);  
  pinMode(button2, INPUT_PULLUP);  
  pinMode(button3, INPUT_PULLUP);  
  pinMode(button4, INPUT_PULLUP);  
 
  //Setup Servos with pins and move to start position
  servo1.attach(2);
  servo1.write(servoState1);

  servo2.attach(3);
  servo2.write(servoState2);

  servo3.attach(4);
  servo3.write(servoState3);

  servo4.attach(5);
  servo4.write(servoState4);

  //tilt switch setup
  pinMode(tiltSwitch,INPUT);
  digitalWrite(tiltSwitch, HIGH);
}

void loop() {
  ////////////////////////////////////////////////////////////////
  //servo 1
  if (digitalRead(button1) == LOW && servoState1 < 160)
  {
    servo1.write(servoState1 + 32);
    servoState1 = servoState1 + 32;
    delay(servoDelay);
  }
  else if (digitalRead(button1) == LOW)
  {
    servo1.write(0);
    servoState1 = 0;
    delay(servoDelay);
  }
  //////////////////////////////////////////////////////////////////
  //servo2
   if (digitalRead(button2) == LOW && servoState2 < 160)
  {
    servo2.write(servoState2 + 32);
    servoState2 = servoState2 + 32;
    delay(servoDelay);
  }
  else if (digitalRead(button2) == LOW)
  {
    servo2.write(0);
    servoState2 = 0;
    delay(servoDelay);
  }

  //////////////////////////////////////////////////////////////////
  //servo3
   if (digitalRead(button3) == LOW && servoState3 < 160)
  {
    servo3.write(servoState3 + 32);
    servoState3 = servoState3 + 32;
    delay(servoDelay);
  }
  else if (digitalRead(button3) == LOW)
  {
    servo3.write(0);
    servoState3 = 0;
    delay(servoDelay);
  }

  //////////////////////////////////////////////////////////////////
  //servo4
   if (digitalRead(button4) == LOW && servoState4 < 160)
  {
    servo4.write(servoState4 + 32);
    servoState4 = servoState4 + 32;
    delay(servoDelay);
  }
  else if (digitalRead(button4) == LOW)
  {
    servo4.write(0);
    servoState4 = 0;
    delay(servoDelay);
  }


  //win state trigger
  if (servoState1 == 32 && servoState2 == 32 && servoState3 == 96 && servoState4 == 128 && digitalRead(tiltSwitch) == LOW)
  {
    //write to win pin low for success!
    digitalWrite(winPin, LOW);
  }

 

}
