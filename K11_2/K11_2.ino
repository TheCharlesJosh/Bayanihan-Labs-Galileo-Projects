/*
  Mood Lighting Cycles Through Illumination Levels

  Created by Bayanihan Labs.
*/

//Pin Variables - We declare the pins used into variables for easy access.
const int redRGB = 3;
const int greenRGB = 5;
const int blueRGB = 6;
const int groundRGB = 4;
const int touchSensor = 7;
boolean isTouched = false;
boolean prevIsTouched = false;

void setup() {
  //Digital pins need to be assigned modes every startup
  pinMode(redRGB, OUTPUT);
  pinMode(greenRGB, OUTPUT);
  pinMode(blueRGB, OUTPUT);
  pinMode(groundRGB, OUTPUT);
  randomColor();
}

void loop() {

 /*
  * These lines of code finds the part where the finger
  * "releases" the touch sensor.
  */

  isTouched = digitalRead(touchSensor);
  if (isTouched == false && prevIsTouched == true) {
      randomColor();
  }
  prevIsTouched = isTouched;
}

/*
 * Random color generator
 * random(min, max) picks a random number from min to max.
 * Since analogWrite goes to 0 to 255, we have to set the
 * min and max accordingly.
 */
void randomColor() {
  analogWrite(redRGB, random(0, 255));
  analogWrite(greenRGB, random(0, 255));
  analogWrite(blueRGB, random(0, 255));
  digitalWrite(groundRGB, LOW);
}



