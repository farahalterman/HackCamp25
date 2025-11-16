#include <ESP32Servo.h>
#include <LiquidCrystal.h>
#include <esp_now.h>
#include <WiFi.h>

//Buttons
int BUTTON_1 = 12;
int BUTTON_2 = 14;
int BUTTON_3 = 27;
int BUTTON_4 = 33;
int BUTTON_5 = 25;
int BUTTON_6 = 26;

uint8_t broadcastAddress[] = {0x08, 0xD1, 0xF9, 0xCE, 0x48, 0xEC};

//Information about the other ESP
esp_now_peer_info_t peerInfo;

char myMsg;
char incomingMsg;

String success;

const int rs = 23, en = 22, d4 = 21, d5 = 19, d6 = 18, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo servo1;
Servo servo2;
Servo servo3;

int servo1Pin = 16;
int servo2Pin = 17;
int servo3Pin = 15;

int minUs = 500;   // SG90 safe minimum
int maxUs = 2700;   // SG90 safe maximum

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
    {'"', {0,0,1}}
};

const int charactersCount = sizeof(characters) / sizeof(characters[0]);
      

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingMsg, incomingData, sizeof(incomingMsg));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Message: ");
  Serial.println(incomingMsg);
  delay(200);
}

 const int* getCharacterValues(char c) {
    for (int i = 0; i < charactersCount; i++) {
      if (characters[i].letter == c) {
        return characters[i].values;
      }
    }
    return nullptr; // not found
  }


void state_0(int servo){
  // 22.5°
  if (servo ==1) servo1.write(23);
  if (servo == 2) servo2.write(23);
  if (servo ==3) servo3.write(23);
}

void state_2(int servo){
    // 67.5°
  if (servo ==1) servo1.write(68);
  else if (servo ==2) servo2.write(68);
  else if (servo == 3) servo3.write(68);
}

void state_3(int servo){
    // 112.5°
  if (servo ==1) servo1.write(113);
  else if (servo ==2) servo2.write(113);
  else if (servo == 3) servo3.write(113);
}

void state_1(int servo){
    // 157.5°
  if (servo == 1) servo1.write(158);
  else if (servo == 2) servo2.write(158);
  else if (servo ==3) servo3.write(158);
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

void setup()
{
  Serial.begin(115200);

  //Buttons
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP); 

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

   // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  //============ SERVOS ===============
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);

  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
  servo3.attach(servo3Pin, minUs, maxUs);

  //LCD
  lcd.begin(16, 2);
}

void loop()
{
  // =========== BUTTONS ============
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

  int Braille_Array[] = {b1,b2,b3,b4,b5,b6};

  char actual_alphabet = findMatchingButton( Braille_Array );

  Serial.println(actual_alphabet);

  for (int i = 0; i< 5; i++){
      // ======== SERVO POSITIONING ===== //
    
      const int* servo_pos= getCharacterValues(incomingMsg);
      if (servo_pos != nullptr) {
      for (int i = 0; i < 3; i++) { 
        switch (servo_pos[i]) {
          case 0: state_0(i + 1); break;
          case 1: state_1(i + 1); break;
          case 2: state_2(i + 1); break;
          case 3: state_3(i + 1); break;
        }
      }
    }
    delay(50);
  }

  //======= SECONDING MESSAGES ======= 

  // Set values to send
  myMsg = actual_alphabet;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myMsg, sizeof(myMsg));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

    // =========== LCD ========== 
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(incomingMsg);
  
  delay(500);
}