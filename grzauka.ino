#include <LiquidCrystal.h>
#define a  -4.81420754311680e-07
#define b  0.000824947169111364
#define c  -0.572414341372402
#define d  243.873039587372
#define HEATER_0 10

double x, y;
double temp;
double e;
double u;
double calka = 0;
int i = 0;
double P = 0; 
double I = 0; 
double D = 0;
double predkosc = 0;
double yi = 0;
double stara = 0;


LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

void setup() {

  lcd.begin( 20, 4 );
  pinMode( HEATER_0, OUTPUT);
}

void loop() {
  temp = analogRead( 14 );
  lcd.setCursor(13, 0);
  lcd.print ("T_zew: ");
  x = temp;
  y = a * x * x * x + b * x * x + c * x + d;
  lcd.setCursor(13, 1);
  lcd.print(y);

  temp = analogRead( 13 );
  lcd.setCursor(0, 0);
  lcd.print("T_wew: ");
  x = temp;
  y = a * x * x * x + b * x * x + c * x + d;
  lcd.setCursor(0, 1);
  lcd.print(y);

  e = 100 - yi;
  predkosc = (u-stara)/0.1;
  calka = calka + e * 0.1;
  P = 255/80;
  I = 0.2;
  D = 1;
  
  u=round(P*e+I*calka+D*predkosc);
  if (u < 0) {
    i = 0;
  }

  if (u > 255) {
    u = 255;
  }
  
  analogWrite(10,u);

  stara = yi;
  delay(100);
  
  if (y > 0 && y < 100) {
    u = 255 / 80 * e + 0.2 * calka;
       digitalWrite(9,LOW);
  }

  else {
    u = 255 / 80 * e;
    digitalWrite(9,HIGH);
  }

/*if (u > 0) {
  if (u < 255) {
      analogWrite(10, u);
    }
    else {
      analogWrite(10, 255);
    }
  }
  else {
    analogWrite(10, 0);
  }*/

  lcd.setCursor(8, 0);
  lcd.print("U:");
  lcd.setCursor(7, 1);
  lcd.print(u);
  lcd.setCursor(0, 2);
  lcd.print("P:");
  lcd.setCursor(0, 3);
  lcd.print(P);
  lcd.setCursor(6, 2);
  lcd.print("I:");
  lcd.setCursor(6, 3);
  lcd.print(I);
  lcd.setCursor(13, 2);
  lcd.print("D:");
  lcd.setCursor(13, 3);
  lcd.print(D);
    
  /* Wlaczenie na 5 sekund
     if (i<50) {
    digitalWrite( HEATER_0, HIGH);
    i++;
    }
    else {
    digitalWrite( HEATER_0, LOW);
    }

    delay(100);*/
}
