/*
  Sliding Door Controller

  Activates the motor attached on the sliding door based on the button pressed.
  The Galileo compares the values when either of the buttons are pressed. From there,
  the motor is instructed to open or close accordingly.

  Created by Bayanihan Labs.
*/

const int directionPin = 4,
          speedPin = 5,
          rackSlide = 20;

int analogValue = 0;

boolean gatePosition = true;

void setup() {
  /*
   * Initialize the digital pins to be configured as output.
   */
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
}

void loop() {
  /*
   * Read the value from the pushbuttons.
   */
  analogValue = analogRead(A0);

  /*
   * The buttons correspond to their respective resistors,
   * which makes it possible to detect which button was pressed
   * even with just one pin to read data from. 
   */

  
  if ((analogValue > 500) && (analogValue < 1000) && !gatePosition) {
    /*
     * Rotates the motor through roughly rackSlide notches on the rack.
     */
    for (int i = 0; i < rackSlide; i++) {
      motorMoveOne(0, 100, 5, 10);
    }

    gatePosition = true;
  }


  else if (analogValue > 1000 && gatePosition) {
    /*
     * Rotates the motor through roughly rackSlide notches on the rack in the other direction.
     */
    for (int i = 0; i < rackSlide; i++) {
      motorMoveOne(1, 100, 5, 10);
    }

    gatePosition = false;
  } else {
    /*
     * Keeps the motor static when no other conditions are met.
     */
    motorMoveOne(1, 0, 0, 0);
  }
}


/*
 * This function is used to rotate the motor in small incremenents at a time.
 */
void motorMoveOne(int motorDirection, int motorSpeed, int motorDelay, int restMultiplier) {
  /*
   * This chunk of code tells the motor to move in one direction for a specific amount of time.
   */
  digitalWrite(directionPin, motorDirection);
  analogWrite(speedPin, motorSpeed);
  delay(motorDelay);

  /*
   * Afterwards, tell the motor to stop.
   */
  digitalWrite(directionPin, motorDirection);
  analogWrite(speedPin, 0);
  delay(motorDelay * restMultiplier);
}

/*
	Troubleshooting:

	Gate not opening/closing properly? Try increasing rackSlide.
	Gate grinding to the sides? Try decreasing rackSlide.
*/
