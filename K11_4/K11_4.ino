/*
  Air Conditioning Control using a temperature sensor

  Using the infrared proximity sensor, we make a piezo buzzer
  beep periodically. Notice how this code makes no use of 
  the delay() function, but uses the millis() function.

  One disadvantage of the delay() function is that the 
  board really does nothing during that period. When you need
  to constantly monitor data, delay() might block this process
  and may cause you not to detect certain happenings.

  Created by Bayanihan Labs.
*/
 
//Pin Variables - We declare the pins used into variables for easy access.
int pinSensor = A0;
int pinLED = 4;

//Data Variables - These will store our data, calculations, and the like.
int rawInput = 0;
float resistance = 0;
float tempCelsius = 0;

/*Constant Variables - These are used to calibrate the program.
 * Bounds are designed to keep the average room temp at 21C
 */
const int upperBound = 24;
const int lowerBound = 18;

void setup () {
  //Digital pins need to be assigned modes every startup
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop () {
  /* This section of the code extracts the rawInput of the temperature
   * sensor then converts it into degrees Celsius.
   * Once a certain temperature is reached (as indicated by maxHeat),
   * the Galileo toggles the LED to the appropriate state.
   */
   
  rawInput = analogRead(pinSensor);
  tempCelsius = processInput(rawInput);
  
  Serial.println(tempCelsius);
  
  if (tempCelsius > upperBound) {
    /*If the measured temperature of the room (stored in tempCelsius) exceeds that of upperBound,
     *the LED (airconditioner) is turned on.
     */
    digitalWrite(pinLED, HIGH);
  } else if (tempCelsius < lowerBound) {
    /*If the room gets cold enough, the LED is turned off signifying that 
     *the airconditioner is off as well.
     */
    digitalWrite(pinLED, LOW);
  }
}

float processInput (int rawInput) {
  /* In this function, we first find the resistance of the temperature sensor, 
   * then convert the obtained resistance into degrees Celsius.
   */
   
  resistance = (1023 - rawInput)*10000/rawInput;
  return (1/(log(resistance/10000)/3975 + 1/298.15)-273.15);
}
