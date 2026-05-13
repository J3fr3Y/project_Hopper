#include "config.h"
#include "moteurs.h"

void initMoteurs() {

  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);

  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
}

void moteurGauche(int vitesse) {

  if (vitesse >= 0) {

    digitalWrite(M1_DIR, HIGH);
    analogWrite(M1_PWM, vitesse);

  } else {

    digitalWrite(M1_DIR, LOW);
    analogWrite(M1_PWM, -vitesse);
  }
}

void moteurDroit(int vitesse) {

  if (vitesse >= 0) {

    digitalWrite(M2_DIR, HIGH);
    analogWrite(M2_PWM, vitesse);

  } else {

    digitalWrite(M2_DIR, LOW);
    analogWrite(M2_PWM, -vitesse);
  }
}

void avancer(int vitesse) {

  moteurGauche(vitesse);
  moteurDroit(vitesse);
}

void tournerDroite(int vitesse) {

  moteurGauche(vitesse);
  moteurDroit(-vitesse);
}

void tournerGauche(int vitesse) {

  moteurGauche(-vitesse);
  moteurDroit(vitesse);
}

void stopMoteurs() {

  moteurGauche(0);
  moteurDroit(0);
}