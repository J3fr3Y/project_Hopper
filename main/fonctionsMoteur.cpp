#include <stdint.h>
#include "Arduino.h"
#include "fonctionsMoteur.h"

const int CRUISE1 = 255;   // tune separately 6.57 v for the left motor
const int CRUISE2 = 255;  // tune separately
const int KICK = 160;     // startup kick
const int KICK_TIME = 150;
const int CRUISE_CALIBRATE = 100;


enum Direction {
  GAUCHE,
  DROITE
};



void initMoteur (int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D){

  pinMode(M1_P, OUTPUT);
  pinMode(M1_D, OUTPUT);
  pinMode(M2_P, OUTPUT);
  pinMode(M2_D, OUTPUT);

  digitalWrite(M1_D, LOW);
  digitalWrite(M2_D, LOW);
  analogWrite(M1_P, 0);
  analogWrite(M2_P, 0);

}

void vitesseMot (int16_t speed1, int16_t speed2, bool forward){

  digitalWrite(M1_DIR, forward ? HIGH : LOW);
  analogWrite(M1_PWM, speed1); 

  digitalWrite(M2_DIR, forward ? HIGH : LOW);
  analogWrite(M2_PWM, speed2);   // 0..255

}

void arretMot (){
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}

/* void drive(bool forward, int s1, int s2) {
  // startup kick to overcome static friction
  motor1(KICK, forward);
  motor2(KICK, forward);
  delay(KICK_TIME);

  vitesseMot(s1,s2,forward);
}*/

void gauche(int16_t puissance){
  vitesseMot(puissance, 0, true);
}

void droite(int16_t puissance){
  vitesseMot(0,puissance,true);
}

void ossiler(int16_t intervalle){
  static int16_t compteur = 0;
  static Direction dir = GAUCHE;

  if (dir == GAUCHE){
    gauche(CRUISE_CALIBRATE);
  }else {
    droite(CRUISE_CALIBRATE);
  }
  compteur++;
  if (compteur>= intervalle){
    dir = (Direction)!dir;
    compteur = 0;
  }
}




