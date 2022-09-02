
/*
 * @author: Evan Plumley
 * 
 * @description Uploaded to the command and control arduino which releases trhe deactivation
 * key once all three puzzles are solved and controls teh "deactivation" of
 * the puzzle box. This sketch also controls an LCD display using the 
 * Arduino LiquidCrystal Library.
 * 
 * 
 * The LCD Pins:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 * 
 */


// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"
#include <Servo.h>

//Defining pins for RFID reader
#define SS_PIN 53
#define RST_PIN 49

//Green LED success indicator let pins
#define LED1 25
#define LED2 24
#define LED3 26
#define PUZZ1SOLVED 34
#define PUZZ2SOLVED 35
#define PUZZ3SOLVED 36

MFRC522 mfrc522(SS_PIN, RST_PIN); //Instance of class
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
String cardUID = "";
bool winFlag = false;

///initialize flag variables for puzzle success
bool puzz1Success = false;
bool puzz2Success = false;
bool puzz3Success = false;

//Flag to trigger puzzle solve sound to make sure it only execute once
int solveSound1 = 0; 
int solveSound2 = 0;
int solveSound3 = 0;  

///////
// notes in the melodyn fro passive speaker:
int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};

//Create servo object
Servo myservo;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("PLUMLEY PUZZLER");
  
  ///////////////////////////////////////////
  // setup RFID reader
  /////////////////////////////////////
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reading UID");

  ////////////////////////////
  //assign LED and puzz solved pin modes and reset to low
  //////////////////////

  //Will be input from other mega boards once they have been solved
  pinMode(PUZZ1SOLVED, INPUT_PULLUP);
  pinMode(PUZZ2SOLVED, INPUT_PULLUP);
  pinMode(PUZZ3SOLVED, INPUT_PULLUP);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);



  /////////////////////////////
  // Setup and center servo with pin 2
  ////////////////////////////
  myservo.attach(2);//connect pin 9 with the control line(the middle line of Servo) 
  myservo.write(90);// move servos to center position -> 90°
}

/*
 * Function to play the puzzle solution chime
 */
void playSolveSound(){
    for (int thisNote = 0; thisNote < 2; thisNote++) {
      // pin6 output the voice, every scale is 0.5 sencond
      tone(6, melody[thisNote], 500);
      delay(500);
    } 
}

/*
 * Function to play the win chime
 */
void playWinSound(){
     for (int thisNote = 0; thisNote < 8; thisNote++) {
      // pin6 output the voice, every scale is 0.5 sencond
      tone(6, melody[thisNote], 1000);
      delay(500);
    }
}

void loop() {

  /////////////////////////////////////////////////////////
  // LCD screen setup
  // (note: line 1 is the second row, since counting begins with 0):
  //////////////////////////////////////////
  lcd.setCursor(2, 1);
  // print the number of seconds since reset:
  if (winFlag)
  {
    lcd.setCursor(0, 1);
    lcd.print("**DEACTIVATED!**");

    //Play win chime
    playWinSound();
  }
  else
  {
    lcd.setCursor(2, 1);
    lcd.print("**ACTIVATED**");
  }

  ///////////////////////////////////////////
  //Look for RFID card presence
  /////////////////////////////////////////
  if(mfrc522.PICC_IsNewCardPresent())
  {
    if(mfrc522.PICC_ReadCardSerial())
    {
      Serial.print("Tag UID:");
      for(byte i = 0; i < mfrc522.uid.size; i++)
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        //cardUID = cardUID + mfrc522.uid.uidByte[i];
      }
      Serial.println();
      winFlag = true;
      mfrc522.PICC_HaltA();
    }
  }

  //////////////////////////////
  // Check to see if a puzzle has been solved and light corresponding green LED
  /////////////////////////////////////////
  
  //success input checks from other boards
  if(digitalRead(PUZZ1SOLVED) == LOW)
  {
    puzz1Success = true;
  }
  if(digitalRead(PUZZ2SOLVED) == LOW)
  {
    puzz2Success = true;
  }
  if(digitalRead(PUZZ3SOLVED) == LOW)
  {
    puzz3Success = true;
  }


  //Flag change checks to activate green LEDs
  if (puzz1Success)
  {
    digitalWrite(LED1, HIGH);
    if (solveSound1 == 0){
      playSolveSound();
      if(solveSound1 < 1) solveSound1 ++;
    }
  }
  if (puzz2Success)
  {
    digitalWrite(LED2, HIGH);
     if (solveSound2 == 0){
      playSolveSound();
      if(solveSound2 < 1) solveSound2 ++;
    }
  
  }
  if (puzz3Success)
  {
    digitalWrite(LED3, HIGH);
     if (solveSound3 == 0){
      playSolveSound();
      if(solveSound3 < 1) solveSound3 ++;
    }
 
  }


  if (puzz1Success && puzz2Success && puzz3Success)
  {
    myservo.write(0);
    delay(1000);
  }

   

  
}
