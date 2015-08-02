/*
  Automatic Illumination Control using a Light Dependent Resistor
  
  Created by Bayanihan Labs.
*/

//Pin Variables - We declare the pins used into variables for easy access.
const int pinLED = 3;
const int pinLDR = A0;

//Data Variables - These will store our data, calculations, and the like.
int rawInput = 0;
int scaledOut = 0;

void setup () {
  //Digital pins need to be assigned modes every startup
  pinMode(pinLED, OUTPUT);
}

void loop () {
  /* This line of code will read the voltage drop caused by the LDR.
   * The Arduino will scale this value from 0-1023, i.e., when the voltage
   * drop is 0 volts, the value read is 0, and when the voltage drop is 5 volts
   * the value read is 1023.
   */
  rawInput = analogRead(pinLDR);
  
  linearlyChange(rawInput);
}

void triggerByBrightness (int rawInput) {
  //Check the ambient brightness level with ~6 Lux (approximately the brightness level when your finger is 0.5cm above the sensor)
  if (rawInput < 400) {
    //When the ambient brightness level is less than ~6 Lux, turn the LED on.
    digitalWrite(pinLED, HIGH);
  } else {
    //Otherwise, turn it off. Energy saving!
    digitalWrite(pinLED, LOW);
  }
}

void linearlyChange(int rawInput) {
  /* Contrary to digitalWrite which only accepts two values for its state (HIGH and LOW),
   * analogWrite accepts state values of 0-255, with 0 (0 volts) being fully off and 255 
   * (5 volts) being fully on. But, only select pins are allowed for analogWrite. For the
   * Intel Galileo, these are pins 3, 5, 6, 9, 10, 11.
   *
   * Since we want to maximize the brightness of the light whenever the ambient brightness 
   * is low and have it off whenever the ambient brightness is high, we have to inversely
   * scale the values 0-1023 to 255-0. We will use the map function for this.
   */
  scaledOut = map(rawInput, 100, 600, 255, 0);

  analogWrite(pinLED, scaledOut);
}

/* Quick Lux (Brightness) Guide from the Grove Starter Kit
 * Sensor Value   Lux     Description
 * 100            <1         
 * 200            ~1      Full moon brightness
 * 300            ~3      City twilight
 * 400            ~6      
 * 500            ~10
 * 600            ~15
 * 700            ~35     Living room
 * 800            ~80     Hallway office light
 * 900            >100    Very dark, overcast day
 */
