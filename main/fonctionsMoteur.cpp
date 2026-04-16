#include "Arduino.h"
#include "fonctionsMoteur.h"

const int M1_PWM = 6;
const int M1_DIR = 7;
const int M2_PWM = 5;
const int M2_DIR = 4;

void initMoteur (){

  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);

}

void vitesseMot (int speed, bool forward){

  digitalWrite(M1_DIR, forward ? HIGH : LOW);
  analogWrite(M1_PWM, speedVal); 

  digitalWrite(M2_DIR, forward ? HIGH : LOW);
  analogWrite(M2_PWM, speedVal);   // 0..255

}

void arretMot (){
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}





