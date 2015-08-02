/*
  Home Security using Proximity IR

  Using the infrared proximity sensor, we make a piezo buzzer
  beep periodically. Notice how this code makes no use of 
  the delay() function, but uses the millis() function.

  One disadvantage of the delay() function is that the 
  board really does nothing during that period. When you need
  to constantly monitor data, delay() might block this process
  and may cause you not to detect certain happenings.

  Created by Bayanihan Labs.
*/

const int piezoPin = 13,
          distancePin = A0,
          duration = 500;
const float tolerance = 400.00;
boolean pulseState = HIGH;
long previousTime;

void setup() {
  /*
   * Initialize the pins as usual, and set board time to
   * previousTime.
   */
  pinMode(piezoPin, OUTPUT);
  previousTime = millis();
}

void loop() {
  /*
   * Store read value to the reading variable.
   * Whenever this reading reaches a certain limit,
   * run the beep function, else, make sure that the
   * piezo will be quiet.
   */
  float reading = analogRead(distancePin);
  
  if (reading > tolerance) {
    beep(millis());
  } else {
    pulseState = LOW;
    digitalWrite(piezoPin, pulseState);
  }
}

void beep (int currentTime) {
  /*
   * Whenever the difference of the current time
   * and the previous logged time exceeds the set duration,
   * flip the state variable and log the current time.
   */
   
  if (currentTime - previousTime >= duration) {
    pulseState ^= HIGH;
    previousTime = currentTime;
  }

  digitalWrite(piezoPin, pulseState);
}

/*
 * Infrared distance sensors usually have a predetermined
 * formula to translate analogRead() values into length
 * (in centimeters). Try researching this one out and
 * change the reading (line 39) and tolerance (line 19) 
 * accordingly.
 */
