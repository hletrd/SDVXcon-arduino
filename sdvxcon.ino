#define BT0_INP 10
#define BT1_INP 11
#define BT2_INP 12
#define BT3_INP 13
#define FX0_INP 8
#define FX1_INP 9

#define VOL0_INPL 6
#define VOL0_INPR 7
#define VOL1_INPL 4
#define VOL1_INPR 5

#define START 3

#define BT0_LED 18
#define BT1_LED 19
#define BT2_LED 20
#define BT3_LED 21
#define FX0_LED 22
#define FX1_LED 23

#define key_BT0 's'
#define key_BT1 'd'
#define key_BT2 'k'
#define key_BT3 'l'
#define key_FX0 'v'
#define key_FX1 'n'
#define key_VOLL0 'q'
#define key_VOLL1 'w'
#define key_VOLR0 'o'
#define key_VOLR1 'p'
#define key_START KEY_RETURN

int started = 0;

void setup() {
  pinMode(BT0_LED, OUTPUT);
  pinMode(BT1_LED, OUTPUT);
  pinMode(BT2_LED, OUTPUT);
  pinMode(BT3_LED, OUTPUT);
  
  pinMode(FX0_LED, OUTPUT);
  pinMode(FX1_LED, OUTPUT);

  pinMode(BT0_INP, INPUT);
  pinMode(BT1_INP, INPUT);
  pinMode(BT2_INP, INPUT);
  pinMode(BT3_INP, INPUT);

  pinMode(FX0_INP, INPUT);
  pinMode(FX1_INP, INPUT);

  pinMode(VOL0_INPL, INPUT_PULLUP);
  pinMode(VOL0_INPR, INPUT_PULLUP);
  pinMode(VOL1_INPL, INPUT_PULLUP);
  pinMode(VOL1_INPR, INPUT_PULLUP);
  
  pinMode(START, INPUT);
  
  Keyboard.begin();
  //Serial.begin(9600);
  
  while(1) {
    if (digitalRead(START) == HIGH) break;
    delay(10);
  }
  delay(200);
  started = millis();
}

int state[2][2] = {LOW, LOW, LOW, LOW};
int gnd[2] = {false, false};
long int lastpressed[2] = {0, 0};

void loop() {
  if (digitalRead(BT0_INP) == HIGH) {
    digitalWrite(BT0_LED, HIGH);
    Keyboard.press(key_BT0);
  } else {
    digitalWrite(BT0_LED, LOW);
    Keyboard.release(key_BT0);
  }

  if (digitalRead(BT1_INP) == HIGH) {
    digitalWrite(BT1_LED, HIGH);
    Keyboard.press(key_BT1);
  } else {
    digitalWrite(BT1_LED, LOW);
    Keyboard.release(key_BT1);
  }

  if (digitalRead(BT2_INP) == HIGH) {
    digitalWrite(BT2_LED, HIGH);
    Keyboard.press(key_BT2);
  } else {
    digitalWrite(BT2_LED, LOW);
    Keyboard.release(key_BT2);
  }

  if (digitalRead(BT3_INP) == HIGH) {
    digitalWrite(BT3_LED, HIGH);
    Keyboard.press(key_BT3);
  } else {
    digitalWrite(BT3_LED, LOW);
    Keyboard.release(key_BT3);
  }


  if (digitalRead(FX0_INP) == HIGH) {
    digitalWrite(FX0_LED, HIGH);
    Keyboard.press(key_FX0);
  } else {
    digitalWrite(FX0_LED, LOW);
    Keyboard.release(key_FX0);
  }

  if (digitalRead(FX1_INP) == HIGH) {
    digitalWrite(FX1_LED, HIGH);
    Keyboard.press(key_FX1);
  } else {
    digitalWrite(FX1_LED, LOW);
    Keyboard.release(key_FX1);
  }

  if (digitalRead(START) == HIGH) {
    Keyboard.press(key_START);
  } else {
    Keyboard.release(key_START);
  }

  if (millis() < started + 2000) {
    digitalWrite(BT0_LED, HIGH);
    digitalWrite(BT1_LED, HIGH);
    digitalWrite(BT2_LED, HIGH);
    digitalWrite(BT3_LED, HIGH);
    digitalWrite(FX0_LED, HIGH);
    digitalWrite(FX1_LED, HIGH);
  }
  
  /*pinMode(VOL0_INPL, OUTPUT);
  pinMode(VOL0_INPR, OUTPUT);
  pinMode(VOL1_INPL, OUTPUT);
  pinMode(VOL1_INPR, OUTPUT);

  digitalWrite(VOL0_INPL, LOW);
  digitalWrite(VOL0_INPR, LOW);
  digitalWrite(VOL1_INPL, LOW);
  digitalWrite(VOL1_INPR, LOW);

  //delayMicroseconds(50);

  digitalWrite(VOL0_INPL, HIGH);
  digitalWrite(VOL0_INPR, HIGH);
  digitalWrite(VOL1_INPL, HIGH);
  digitalWrite(VOL1_INPR, HIGH);

  //delayMicroseconds(50);

  pinMode(VOL0_INPL, INPUT);
  pinMode(VOL0_INPR, INPUT);
  pinMode(VOL1_INPL, INPUT);
  pinMode(VOL1_INPR, INPUT);

  //delayMicroseconds(50);*/
  
  if (digitalRead(VOL0_INPL) == LOW && digitalRead(VOL0_INPR) == LOW) {
    gnd[0] = true;
    Keyboard.release(key_VOLL0);
    Keyboard.release(key_VOLL1);
  } else if (gnd[0] == true && digitalRead(VOL0_INPL) == HIGH && digitalRead(VOL0_INPR) == LOW) {
    state[0][0] = HIGH;
    gnd[0] = false;
    Keyboard.release(key_VOLL0);
    Keyboard.release(key_VOLL1);
  } else if (state[0][0] == HIGH && digitalRead(VOL0_INPL) == HIGH && digitalRead(VOL0_INPR) == HIGH && gnd[0] == false) {
    Keyboard.release(key_VOLL0);
    Keyboard.press(key_VOLL1);
    lastpressed[0] = millis();
    state[0][0] = LOW;
    //Serial.println("Left R");
  } else if (gnd[0] == true && digitalRead(VOL0_INPL) == LOW && digitalRead(VOL0_INPR) == HIGH) {
    state[0][1] = HIGH;
    gnd[0] = false;
    Keyboard.release(key_VOLL0);
    Keyboard.release(key_VOLL1);
  } else if (state[0][1] == HIGH && digitalRead(VOL0_INPL) == HIGH && digitalRead(VOL0_INPR) == HIGH && gnd[0] == false) {
    Keyboard.release(key_VOLL1);
    Keyboard.press(key_VOLL0);
    lastpressed[0] = millis();
    state[0][1] = LOW;
    //Serial.println("Left L");
  }

  if (digitalRead(VOL1_INPL) == LOW && digitalRead(VOL1_INPR) == LOW) {
    gnd[1] = true;
    Keyboard.release(key_VOLR0);
    Keyboard.release(key_VOLR1);
  } else if (gnd[1] == true && digitalRead(VOL1_INPL) == HIGH && digitalRead(VOL1_INPR) == LOW) {
    state[1][0] = HIGH;
    gnd[1] = false;
    Keyboard.release(key_VOLR0);
    Keyboard.release(key_VOLR1);
  } else if (state[1][0] == HIGH && digitalRead(VOL1_INPL) == HIGH && digitalRead(VOL1_INPR) == HIGH && gnd[1] == false) {
    Keyboard.release(key_VOLR0);
    Keyboard.press(key_VOLR1);
    lastpressed[1] = millis();
    state[1][0] = LOW;
  } else if (gnd[1] == true && digitalRead(VOL1_INPL) == LOW && digitalRead(VOL1_INPR) == HIGH) {
    Keyboard.release(key_VOLR0);
    Keyboard.release(key_VOLR1);
    state[1][1] = HIGH;
    gnd[1] = false;
  } else if (state[1][1] == HIGH && digitalRead(VOL1_INPL) == HIGH && digitalRead(VOL1_INPR) == HIGH && gnd[1] == false) {
    Keyboard.release(key_VOLR1);
    Keyboard.press(key_VOLR0);
    lastpressed[1] = millis();
    state[1][1] = LOW;
  }//

  if (millis() > lastpressed[0] + 100) {
    Keyboard.release(key_VOLL0);
    Keyboard.release(key_VOLL1);
  }
  if (millis() > lastpressed[1] + 100) {
    Keyboard.release(key_VOLR0);
    Keyboard.release(key_VOLR1);
  }
}//
