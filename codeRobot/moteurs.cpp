#include "moteurs.h"
#include <Arduino.h>

int16_t M1_PWM;
int16_t M1_DIR;
int16_t M2_PWM;
int16_t M2_DIR;

//parametres utilisés pour la fonction ossiler
int16_t VITESSE_CALIBRATION = 90;
int16_t intervalle = 10;
enum Direction {
    AVANCER,
    RECULER
};
Direction dir = AVANCER;
int16_t compteur = 5;

void initialisationMoteur(int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D){
  M1_PWM = M1_P;
  M1_DIR = M1_D;
  M2_PWM = M2_P;
  M2_DIR = M2_D;

  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);

}

void moteurGauche(int16_t vitesse, bool avancer){
  digitalWrite(M1_DIR, avancer ? HIGH : LOW);
  analogWrite(M1_PWM, vitesse);

}

void moteurDroit(int16_t vitesse, bool avancer){
  digitalWrite(M2_DIR, avancer ? HIGH : LOW);
  analogWrite(M2_PWM, vitesse);
}
void moteurs (int16_t vitesse, bool avancer){
  moteurGauche(vitesse,avancer);
  moteurDroit(vitesse, avancer);
}

void stop(){
  moteurs(0,false);
}
/*
void ossiler(){
  if (dir == AVANCER) {
    moteurGauche(VITESSE_CALIBRATION,true);
    moteurDroit(VITESSE_CALIBRATION,true);
  } else {
    moteurGauche(VITESSE_CALIBRATION,false);
    moteurDroit(VITESSE_CALIBRATION,false);
  }

  compteur++;

  if (compteur >= intervalle) {
    dir = (Direction)!dir;
    compteur = 0;
  }

}
*/


