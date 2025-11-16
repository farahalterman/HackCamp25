// C++ code


int SPACE_BAR = 26;
int BUTTON_1 = 27;
int BUTTON_2 = 14;
int BUTTON_3 = 12;
int BUTTON_4 = 32;
int BUTTON_5 = 33;
int BUTTON_6 = 25;

void setup() {
  Serial.begin(115200);
   
  pinMode(SPACE_BAR, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP); 


  delay(1000);
  Serial.println("Starting now");
}

void loop() {

  /* Reading the state of each button */
  int space = digitalRead(SPACE_BAR);
  int b1 = digitalRead(BUTTON_1);
  int b2 = digitalRead(BUTTON_2);
  int b3 = digitalRead(BUTTON_3);
  int b4 = digitalRead(BUTTON_4);
  int b5 = digitalRead(BUTTON_5);
  int b6 = digitalRead(BUTTON_6);

  Serial.print(
    String(b1) +
    String(b2) +
    String(b3) +
    String(b4) +
    String(b5) +
    String(b6)
  );
  Serial.println();

  delay(500);
}
