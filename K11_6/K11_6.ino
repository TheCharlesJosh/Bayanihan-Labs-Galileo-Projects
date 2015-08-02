/*
  Energy-saving Escalator via Proximity Sensor

  This program is remarkably similar to K11-3 (Home Security
  using Proximity IR), wherein instead of using a piezo buzzer,
  we are using a DC motor connected to a motor shield.

  Created by Bayanihan Labs.
*/

const int directionPin = 4,
          speedPin = 5,
          distancePin = A0,
          motorSpeed = 50,
          duration = 5000;
const float tolerance = 400.00;
boolean isMoving = false;
long previousTime;

void setup() {
  /*
   * Initialize the pins as usual, set board time to
   * previousTime, and set the rotation of the board.
   */
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  previousTime = millis();

  digitalWrite(directionPin, HIGH);
}

void loop() {
  /*
   * On standby, the escalator will not move.
   * Upon trigger by proximity, ensure that the escalator
   * will be powered for a period 'duration' after standby.
   * Standby happens when the proximity sensor does not
   * detect anything nearby.
   */
  float reading = analogRead(distancePin);
  
  if (reading > 400.00) {
    if (isMoving == false) {
      isMoving = true;      
    }
    previousTime = currentTime;
  }

  moveTheEscalator(millis());
}

void moveTheEscalator(int currentTime) {
  /*
   * Whenever the difference of the current time
   * and the previous logged time exceeds the set duration,
   * flip the state variable and log the current time.
   * 
   * With the motor shield, control of the motor becomes
   * easy. directionPin controls if it moves clockwise or
   * counterclockwise, speedPin controls its speed.
   */
   
  if (currentTime - previousTime >= duration) {
    isMoving ^= true;
    previousTime = currentTime;
  }
  
  if (isMoving) {
    analogWrite(speedPin, motorSpeed);
  } else {
    analogWrite(speedPin, 0);
  }
}

/*
 * Infrared distance sensors usually have a predetermined
 * formula to translate analogRead() values into length
 * (in centimeters). Try researching this one out and
 * change the reading (line 39) and tolerance (line 19) 
 * accordingly.
 * 
 * To adjust the time the motor is moving, change the duration
 * variable (line 14). To change the motor rotation, change
 * line 28.
 */
