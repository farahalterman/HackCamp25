void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  struct ButtonEntry {
    int values[6];
    char letter;
  }

const ButtonEntry buttons[] = {
    {{0,1,1,1,1,1}, 'a'},
    {{0,0,1,1,1,1}, 'b'},
    {{0,1,0,1,1,1}, 'c'},
    {{0,1,0,0,1,1}, 'd'},
    {{0,1,0,1,1,1}, 'e'},
    {{0,0,1,0,1,1}, 'f'},   
    {{0,0,1,0,0,1}, 'g'},
    {{0,0,1,0,0,1}, 'h'},   
    {{1,0,0,1,1,1}, 'i'},
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
    {{1,0,0,0,0,0}, 'w'},
    {{0,1,0,0,1,0}, 'x'},
    {{0,1,0,0,0,0}, 'y'},
    {{0,1,0,1,0,0}, 'z'},
    {{1,0,1,1,1,1}, ','},
    {{1,0,0,1,1,1}, ';'},
    {{1,0,1,0,1,1}, ':'},
    {{1,0,1,1,0,1}, '.'},
    {{1,0,0,1,0,1}, '?'},
    {{1,0,0,1,1,0}, '!'},
    {{1,1,0,1,1,1}, '\''}
};

  const buttonsCount = sizeof(buttons) / sizeof(buttons[0]);

  bool arraysEqual(const int a[], const int b[], int length) {
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

  char findMatchingButton(const int input[6]) {
    for (int i = 0; i < buttonsCount; i++) {
      if (arraysEqual(input, buttons[i].pattern, 6)) {
        return buttons[i].letter;  // match found, return corresponding char
      }
    }
    return '\0';  // no match found
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char input = Serial.read();   // read ONE character
    Serial.println(String("You printed:"+ input));
  }
}
