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


  delay(2000);
  Serial.println("Starting now");
}

  struct ButtonEntry {
    int values[6];
    char letter;
  };

const ButtonEntry buttons[] = {
    {{0,1,1,1,1,1}, 'a'},
    {{0,0,1,1,1,1}, 'b'},
    {{0,1,1,0,1,1}, 'c'},
    {{0,1,1,0,0,1}, 'd'},
    {{0,1,1,1,0,1}, 'e'},
    {{0,0,1,0,1,1}, 'f'},   
    {{0,0,1,0,0,1}, 'g'},
    {{0,0,1,1,0,1}, 'h'},   
    {{1,0,1,0,1,1}, 'i'},
    {{1,0,1,0,0,1}, 'j'},
    {{0,1,0,1,1,1}, 'k'},
    {{0,0,0,1,1,1}, 'l'},
    {{0,1,0,0,1,1}, 'm'},
    {{0,1,0,0,0,1}, 'n'},
    {{0,1,0,1,0,1}, 'o'},
    {{0,0,0,0,1,1}, 'p'},
    {{0,0,0,0,0,1}, 'q'},
    {{0,0,0,1,0,1}, 'r'},
    {{1,0,0,0,1,1}, 's'},
    {{1,0,0,0,0,1}, 't'},
    {{0,1,0,1,1,0}, 'u'},
    {{0,0,0,1,1,0}, 'v'},
    {{1,0,1,0,0,0}, 'w'},
    {{0,1,0,0,1,0}, 'x'},
    {{0,1,0,0,0,0}, 'y'},
    {{0,1,0,1,0,0}, 'z'},
    {{1,0,1,1,1,1}, ','},
    {{1,0,0,1,1,1}, ';'},
    {{1,0,1,1,0,1}, ':'},
    {{1,0,1,1,0,1}, '.'},
    {{1,0,0,1,0,1}, '?'},
    {{1,0,0,1,1,0}, '!'},
    {{1,1,0,1,1,1}, '\''}
};

  const int buttonsCount = sizeof(buttons) / sizeof(buttons[0]);

  bool arraysEqual(const int a[], const int b[], int length) {
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}


  char findMatchingButton(const int input[6]) {
    for (int i = 0; i < buttonsCount; i++) {
      if (arraysEqual(input, buttons[i].values, 6)) {
        return buttons[i].letter;  // match found, return corresponding char
      }
    }
    return '\0';  // no match found
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
/*
  Serial.print(
    String(b1) +
    String(b2) +
    String(b3) +
    String(b4) +
    String(b5) +
    String(b6)
  );
*/
  
  
  int Braille_Array[] = {b1,b2,b3,b4,b5,b6};

  char actual_alphabet = findMatchingButton( Braille_Array );

  Serial.println(actual_alphabet);

  delay(3000);

}

