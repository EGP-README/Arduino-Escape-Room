int val;
int lightVal;
int tempPin = 1;
int lightPin = 0;
int winPin = 22;

int lightIndicator = 51;
int heatIndicator = 49;

/*
  @author Evan Plumley
  @description Riddle 3 consits of a light sensor, and a temperature sensor.
  The light sensor must be belwo a threshold that is considered dark. and
  The heat sensor must reach a minumim of 49 Celsius to trigger the win state.
  Participants generally solve this puzzle by covering the light sensor
  with thier hand while holding a light up to the heat sensor.
  Sensor reading output included and commented out.
*/

void setup()
{
  Serial.begin(9600);
  //set win pin
  pinMode(winPin, OUTPUT);
  digitalWrite(winPin, HIGH);
  pinMode(lightIndicator, OUTPUT);
  pinMode(heatIndicator, OUTPUT);
  
}
void loop()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;

  /*
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);
 */
 
  /* uncomment this to get temperature in farenheight
  Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print("*F");
  Serial.println();
  */

  // reads the input on analog pin A0 (value between 0 and 1023)
  lightVal = analogRead(lightPin);
  /*
  Serial.print("Analog reading: ");
  Serial.print(lightVal);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (lightVal < 10) {
    Serial.println(" - Dark");
  } else if (lightVal < 200) {
    Serial.println(" - Dim");
  } else if (lightVal < 500) {
    Serial.println(" - Light");
  } else if (lightVal < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  */

  //delay(500);

  if(lightVal <= 10)
  {
    digitalWrite(lightIndicator, HIGH);
  }
  else
  {
    digitalWrite(lightIndicator, LOW);
  }

  if(cel >= 30)
  {
    digitalWrite(heatIndicator, HIGH);
  }
  else
  {
    digitalWrite(heatIndicator, LOW);
  }

  //win state trigger
  if(lightVal <= 10 && cel >= 30)
  {
    //write to win pin low for success!
    digitalWrite(winPin, LOW);
    Serial.println("WIN!!");
  }
}
