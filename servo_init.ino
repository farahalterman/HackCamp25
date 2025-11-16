#include <ESP32Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int servo1Pin = 16;
int servo2Pin = 17;
int servo3Pin = 15;

int minUs = 500;
int maxUs = 2700;


void state_0(int servo){
  if (servo ==1) servo1.write(23);
  else if (servo ==2) servo2.write(23);
  else if (servo ==3) servo3.write(23);
}

void state_1(int servo){
  if (servo ==1) servo1.write(68);
  else if (servo ==2) servo2.write(68);
  else if (servo ==3) servo3.write(68);
  delay(1000);
}

void state_2(int servo){
  if (servo ==1) servo1.write(113);
  else if (servo ==2) servo2.write(113);
  else if (servo ==3) servo3.write(113);
  delay(1000);
}

void state_3(int servo){
  if (servo ==1) servo1.write(158);
  else if (servo ==2) servo2.write(158);
  else if (servo ==3) servo3.write(158);
  delay(1000);
}


void setup() {
  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
  servo3.attach(servo3Pin, minUs, maxUs);

  for (int i = 1; i <= 3; i++)
    state_0(i);
  delay(4000);

  for (int i = 1; i <= 3; i++)
    state_1(i);
  delay(1000);

  for (int i = 1; i <= 3; i++)
    state_2(i);
  delay(1000);

  for (int i = 1; i <= 3; i++)
    state_3(i);
  delay(1000);

  for (int i = 1; i <= 3; i++)
    state_0(i);
}

void loop() {}