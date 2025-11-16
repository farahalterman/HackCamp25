/*
 Reads the push-button state
 * HELLOOOOOO THIS IS NEW HAHAHA
*/

const int buttonPin = 12;
int buttonState = 0; // stores the state of the button


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {

  buttonState = digitalRead(buttonPin); //checks if button is pressed

  if ( buttonState ==  HIGH )
  {
    Serial.println("PRESSED");
  }
  else
  {
    Serial.println("not pressed");
  }

  delay(500);
}
