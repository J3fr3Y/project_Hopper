#include "HardwareSerial.h"
#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 85 //last ideal 102
#define CRUISE_PID 85  //last ideal 102
#define CRUISE_CALIBRATE 110 //last ideal 110
#define MAX_CRUISE 200 //last ideal 200
#define CENTRE 1000
#define VITESSE_POINTILLE 85
#define VITESSE_ANGLE_DROIT 90
#define VITESSE_ANGLE_30_INTERIEUR 60
#define VITESSE_ANGLE_30_EXTERIEUR 90
#define MAX_TEMPS_POINTILLE 350

int16_t erreur;
int16_t ancienneErreur = 0;
float Kp = 0.35;  //last ideal kp = 0.35
float Kd = 3.0;   //last ideal kd = 2.8
float correction;
float P;
float D;

int16_t seuils[NB_CAPTEURS];
uint32_t dernierTempsLigne = 0;

enum CasParcours {
  LIGNE_NORMALE,
  LIGNE_POINTILLEE,
  ANGLE_30_GAUCHE,
  ANGLE_30_DROITE,
  ANGLE_DROIT_GAUCHE,
  ANGLE_DROIT_DROITE
};

bool capteurSurNoir(uint16_t sensor[], uint8_t index) {
  return sensor[index] > seuils[index];
}

CasParcours detecterCasParcours(uint16_t sensor[]) {
  bool gauche = capteurSurNoir(sensor, 0);
  bool centre = capteurSurNoir(sensor, 1);
  bool droite = capteurSurNoir(sensor, 2);

  if (!gauche && !centre && !droite) {
    return LIGNE_POINTILLEE;
  }

  if (gauche && droite) {
    if (ancienneErreur <= 0) {
      return ANGLE_DROIT_GAUCHE;
    }
    return ANGLE_DROIT_DROITE;
  }

  if (gauche && !centre && !droite) {
    return ANGLE_DROIT_GAUCHE;
  }

  if (!gauche && !centre && droite) {
    return ANGLE_DROIT_DROITE;
  }

  if (gauche && centre && !droite) {
    return ANGLE_30_GAUCHE;
  }

  if (!gauche && centre && droite) {
    return ANGLE_30_DROITE;
  }

  return LIGNE_NORMALE;
}

void tournerAngleDroit(bool gauche) {
  if (gauche) {
    moteurGauche(VITESSE_ANGLE_DROIT, true);
    moteurDroit(VITESSE_ANGLE_DROIT, false);
  } else {
    moteurGauche(VITESSE_ANGLE_DROIT, false);
    moteurDroit(VITESSE_ANGLE_DROIT, true);
  }
}

void suivreAngle30(bool gauche) {
  if (gauche) {
    moteurGauche(VITESSE_ANGLE_30_EXTERIEUR, true);
    moteurDroit(VITESSE_ANGLE_30_INTERIEUR, true);
  } else {
    moteurGauche(VITESSE_ANGLE_30_INTERIEUR, true);
    moteurDroit(VITESSE_ANGLE_30_EXTERIEUR, true);
  }
}

void suivrePointille() {
  if (millis() - dernierTempsLigne < MAX_TEMPS_POINTILLE) {
    moteurs(VITESSE_POINTILLE, true);
  } else {
    tournerAngleDroit(ancienneErreur <= 0);
  }
}

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

  initialisationCapteur(capteur, pinsCapteurs, nbCapteurs);
  initialisationMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage(QTRSensors &capteur) {
  for (uint8_t i = 0; i < 200; i++) {
    capteur.calibrate();  //Fonction de la librairie*
  }
  moteurGauche(CRUISE_CALIBRATE, true);
  moteurDroit(CRUISE_CALIBRATE, false);
  delay(500);
  stop();

  for (uint8_t i = 0; i < 200; i++) {
    capteur.calibrate();  //Fonction de la librairie
  }
  moteurGauche(CRUISE_CALIBRATE, false);
  moteurDroit(CRUISE_CALIBRATE, true);
  delay(800);
  stop();
  for (int i = 0; i < 3; i++) {
    seuils[i] =
      (capteur.calibrationOn.minimum[i] + capteur.calibrationOn.maximum[i]) / 2;
  }
  dernierTempsLigne = millis();
}

void suivreLigne(QTRSensors &capteur) {
  uint16_t sensor[NB_CAPTEURS];
  int16_t position = capteur.readLineBlack(sensor);
  CasParcours casParcours = detecterCasParcours(sensor);

  if (casParcours != LIGNE_POINTILLEE) {
    dernierTempsLigne = millis();
  }

  if (casParcours == LIGNE_POINTILLEE) {
    suivrePointille();
    return;
  }

  if (casParcours == ANGLE_DROIT_GAUCHE) {
    ancienneErreur = -CENTRE;
    tournerAngleDroit(true);
    return;
  }

  if (casParcours == ANGLE_DROIT_DROITE) {
    ancienneErreur = CENTRE;
    tournerAngleDroit(false);
    return;
  }

  if (casParcours == ANGLE_30_GAUCHE) {
    ancienneErreur = -CENTRE / 2;
    suivreAngle30(true);
    return;
  }

  if (casParcours == ANGLE_30_DROITE) {
    ancienneErreur = CENTRE / 2;
    suivreAngle30(false);
    return;
  }

  if (sensor[1] > seuils[1] && sensor[0] < seuils[0] && sensor[2] < seuils[2]) {
    ancienneErreur = 0;
    moteurs(CRUISE, true);
  } else {
    erreur = position - CENTRE;
    P = Kp * erreur;

    D = Kd * (erreur - ancienneErreur);
    correction = P + D;

    int16_t vitesseG = CRUISE_PID + correction;
    int16_t vitesseD = CRUISE_PID - correction;

    vitesseG = constrain(vitesseG, 0, MAX_CRUISE);
    vitesseD = constrain(vitesseD, 0, MAX_CRUISE);

    ancienneErreur = erreur;

    moteurGauche(vitesseG, true);
    moteurDroit(vitesseD, true);
  }
}
