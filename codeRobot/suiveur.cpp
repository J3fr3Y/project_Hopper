#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"

int vitesseBase = 90;
int vitesseMax = 255;

float Kp = 0.12;
float Ki = 0.0;
float Kd = 0.25;

int erreurPrecedente = 0;
float sommeErreurs = 0;

void suivreLigne() {

  int position = lirePosition();

  int erreur = position - 1000;

  sommeErreurs += erreur;

  int derivee = erreur - erreurPrecedente;

  int correction =
      Kp * erreur
    + Ki * sommeErreurs
    + Kd * derivee;

  erreurPrecedente = erreur;

  int vg = vitesseBase + correction;
  int vd = vitesseBase - correction;

  vg = constrain(vg, -vitesseMax, vitesseMax);
  vd = constrain(vd, -vitesseMax, vitesseMax);

  moteurGauche(vg);
  moteurDroit(vd);
}