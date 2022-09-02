//www.elegoo.com
//2016.12.9

/* 
   @author Evan Plumley
   @description Riddle 2 consists of a fan that must be stopped from spinning, 
   a water depth sensor and a keypad where a secret code must be entered. The
   water depth sensor must be dipped in water to halt the fan and the the 
   participant can type in the secret code to solve the puzzle
                         
*/
#include <Keypad.h>

//LED pins for fan indicator
#define LED_GREEN 23
#define LED_RED 22

//Motor pins
#define ENABLE 13
#define DIRA 11
#define DIRB 12



const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the two-dimensional array on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//initialize answer string
String answer = "";
int winPin = 52;

//initialiazations for water sensor
int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];
bool waterDipped = false;

//flag for fan
bool fanStopped = false;


void setup(){
  Serial.begin(9600);
  pinMode(winPin, OUTPUT);
  digitalWrite(winPin, HIGH);

  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  //set LEDs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  
  
}
  
void loop(){
  //water depth value
  int waterValue = analogRead(adc_id); // get adc value
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    //Serial.println(customKey);
    if(customKey == '*'){
      answer = "";
    }
    else{
      answer = answer + customKey;
    }
    //Serial.println(answer);
    
  } 

  if (waterValue > 100){
    waterDipped = true;
  }

  /*
  //print water depth to serial
  if(((HistoryValue>=waterValue) && ((HistoryValue - waterValue) > 10)) || ((HistoryValue<waterValue) && ((waterValue - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC %d level is %d\n",adc_id, waterValue);
      //Convert binary numbers "adc_id" and "value" into strings, and store the whole string "ADC "adc_id" level is "value"\n"in C.
      
      Serial.print(printBuffer);
      HistoryValue = waterValue;
    }
   */


  /*
   * Fan Operation
   */
  //---fast/slow stop example
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);

  if(waterDipped){
    digitalWrite(ENABLE,LOW); //enable on
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  }

  //win state trigger
  if(answer == "103" && waterDipped){
    //write win pin low for success!
    digitalWrite(winPin, LOW);
  }
  
}
