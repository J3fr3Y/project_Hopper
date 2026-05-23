#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>
#include <QTRSensors.h>


int vitesseBase = 90;
int vitesseMax = 255;

float Kp = 0.12;
float Ki = 0.0;
float Kd = 0.25;

int erreurPrecedente = 0;
float sommeErreurs = 0;

int calculCorrectionPID(int erreur) {

  sommeErreurs += erreur;

  int derivee = erreur - erreurPrecedente;

  int correction =
      Kp * erreur
    + Ki * sommeErreurs
    + Kd * derivee;

  erreurPrecedente = erreur;

  return correction;
}

int limiterVitesse(int vitesse) {

  return constrain(vitesse, -vitesseMax, vitesseMax);
}

void suivreLigne() {

  int position = lirePosition();

  int erreur = position - 1000;

  int correction = calculCorrectionPID(erreur);

  int vg = vitesseBase + correction;
  int vd = vitesseBase - correction;

  vg = limiterVitesse(vg);
  vd = limiterVitesse(vd);

  moteurGauche(vg);
  moteurDroit(vd);
}

void rechercheLigne() {

  tournerDroite(80);
}

void gererIntersection() {

  avancer(vitesseBase);
}

void gererArrivee() {

  stopMoteurs();
}

void gestionDepart() {

  avancer(vitesseBase);
}