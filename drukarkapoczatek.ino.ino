#include <stdlib.h>

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#ifndef X_CS_PIN
#define X_CS_PIN           53
#endif

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#ifndef Y_CS_PIN
#define Y_CS_PIN           49
#endif

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#ifndef Z_CS_PIN
#define Z_CS_PIN           40
#endif

#define X_MIN_PIN           3
#ifndef X_MAX_PIN
#define X_MAX_PIN           2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19



int k = 0; //kroki
int i1 = 0;//kierunek 1
int i2 = 0;//kierunek 2
int i3 = 0;//kierunek 3
int a = 0; //sterowanie lancuchem
//int b = 0; //silnik 2 w programie
//int c = 0; //silnik 3 w programie
int s1 = 0; //silnik 1 na sterowniku
int s2 = 0; //silnik 2 na sterowniku
int s3 = 0; //silnik 3 na sterowniku
String msg;
bool fok = 0;

//ustawianie zmiennych

void setup() {
  //put your setup code here, to run once:`
  //DEKLARACJA OSI POOENIA I KIERUNKOW
  Serial.begin(115200);
  pinMode(X_ENABLE_PIN , OUTPUT);
  digitalWrite(X_ENABLE_PIN, 0);
  pinMode(X_DIR_PIN, OUTPUT);
  digitalWrite(X_DIR_PIN, i1);
  pinMode(X_STEP_PIN , OUTPUT);
  digitalWrite(X_STEP_PIN , 0);

  pinMode(Y_ENABLE_PIN , OUTPUT);
  digitalWrite(Y_ENABLE_PIN, 0);
  pinMode(Y_DIR_PIN, OUTPUT);
  digitalWrite(Y_DIR_PIN, i2);
  pinMode(Y_STEP_PIN , OUTPUT);
  digitalWrite(Y_STEP_PIN , 0);

  pinMode(Z_ENABLE_PIN , OUTPUT);
  digitalWrite(Z_ENABLE_PIN, 0);
  pinMode(Z_DIR_PIN, OUTPUT);
  digitalWrite(Z_DIR_PIN, i3);
  pinMode(Z_STEP_PIN , OUTPUT);
  digitalWrite(Z_STEP_PIN , 0);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

}
//DANIE PREDKOSCI NA SILNIKI

void loop() {
  // druk info z krancowek
  //Serial.println(digitalRead(X_MAX_PIN));
  //Serial.println(digitalRead(Y_MAX_PIN));
  //Serial.println(digitalRead(Z_MAX_PIN));

  if ((digitalRead(X_MAX_PIN) == 0 || digitalRead(X_MAX_PIN) == 1 && i1 == 1 ) && s1 > 0) {
    digitalWrite(X_STEP_PIN , HIGH);
    s1 = s1 - 1;
  }
  if ((digitalRead(Y_MAX_PIN) == 0 || digitalRead(Y_MAX_PIN) == 1 && i2 == 1 ) && s2 > 0) {
    digitalWrite(Y_STEP_PIN , HIGH);
    s2 = s2 - 1;
  }
  if (digitalRead((Z_MAX_PIN) == 0 || digitalRead(Z_MAX_PIN) == 1 && i3 == 1 ) && s3 > 0) {
    digitalWrite(Z_STEP_PIN , HIGH);
    s3 = s3 - 1;
  }
  //krancwki gra jazda
  //jazda ww dol
  delay(1);
  digitalWrite(X_STEP_PIN , LOW);
  digitalWrite(Y_STEP_PIN , LOW);
  digitalWrite(Z_STEP_PIN , LOW);
  delay(1);

  while (Serial.available() > 0) {
    msg = Serial.readStringUntil('\n');

    sscanf(msg.c_str(), "a %d b %d c %d \n", &s1, &s2, &s3);
    fok = 1;
    i1 = s1 < 0; digitalWrite(X_DIR_PIN, i1);
    s1 = abs(s1);

    i2 = s2 < 0; digitalWrite(Y_DIR_PIN, i2);
    s2 = abs(s2);

    i3 = s3 < 0;
    digitalWrite(Z_DIR_PIN, i3);
    s3 = abs(s3);

    //Serial.println(s1);
    //Serial.println(s2);
    //Serial.println(s3);

  }
  /*k = k + 1;
    if (k == 5000) {
    k = 0;
    i = !i;
    digitalWrite(X_DIR_PIN, i);
    digitalWrite(Y_DIR_PIN, i);
    digitalWrite(Z_DIR_PIN, i);
    }

  */
    // Potwierdzenie zakoczenia ruchu
    if (s1 == 0 && s2 == 0 && s3 == 0 && fok == 1) {
      Serial.println("Zadanie wykonane, moj panie. Twoj unizony sluga oczekuje na nowe zadanie");
      fok = 0;
    }
}


