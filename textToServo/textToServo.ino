void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
struct CharacterEntry {
  char letter;
  int values[3];
};

const CharacterEntry characters[] = {
    {'a', {1,0,0}},
    {'b', {1,1,0}},
    {'c', {3,0,0}},
    {'d', {3,2,0}},
    {'e', {1,2,0}},
    {'f', {3,1,0}},
    {'g', {3,3,0}},
    {'h', {1,3,0}},
    {'i', {2,1,0}},
    {'j', {2,3,0}},
    {'k', {1,0,1}},
    {'l', {1,1,1}},
    {'m', {3,0,1}},
    {'n', {3,2,1}},
    {'o', {1,2,1}},
    {'p', {3,1,1}},
    {'q', {3,3,1}},
    {'r', {1,3,1}},
    {'s', {2,1,1}},
    {'t', {2,3,1}},
    {'u', {1,0,3}},
    {'v', {1,1,3}},
    {'w', {2,3,2}},
    {'x', {3,0,3}},
    {'y', {3,2,3}},
    {'z', {1,2,3}},
    {',', {0,1,0}},
    {';', {0,1,1}},
    {':', {0,3,1}},
    {'.', {0,3,2}},
    {'?', {0,1,3}},
    {'!', {0,3,1}},
    {'\'', {0,0,1}}
};

const int charactersCount = sizeof(characters) / sizeof(characters[0]);

const int* getCharacterValues(char c) {
  for (int i = 0; i < charactersCount; i++) {
    if (characters[i].letter == c) {
      return characters[i].values;
    }
  }
  return nullptr; // not found
}


const int comma[]     = {0,1,0};   // ,
const int semicolon[] = {0,1,1};   // ;
const int colon[]     = {0,3,1};   // :
const int period[]    = {0,3,2};   // .
const int question[]  = {0,1,3};   // ?
const int exclaim[]   = {0,3,1};   // !
const int apostrophe[]= {0,0,1};   // ‘


}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char input = Serial.read();   // read ONE character
    Serial.println(String("You printed:"+ input));
  }
}
