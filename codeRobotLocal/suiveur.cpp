#include "HardwareSerial.h"
#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 102 //last ideal 102
#define CRUISE_PID 102  //last ideal 102
#define CRUISE_CALIBRATE 110 //last ideal 110
#define MAX_CRUISE 200 //last ideal 200
#define CENTRE 1000

int16_t erreur;
int16_t ancienneErreur = 0;
float Kp = 0.35;  //last ideal kp = 0.35
float Kd = 2.8;   //last ideal kd = 2.8
float correction;
float P;
float D;

int16_t seuils[NB_CAPTEURS];

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

  initialisationCapteur(capteur, pinsCapteurs, nbCapteurs);
  initialisationMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage(QTRSensors &capteur) {
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();  //Fonction de la librairie*
  }
  moteurGauche(CRUISE_CALIBRATE, true);
  moteurDroit(CRUISE_CALIBRATE, false);
  delay(500);
  stop();

  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();  //Fonction de la librairie
  }
  moteurGauche(CRUISE_CALIBRATE, false);
  moteurDroit(CRUISE_CALIBRATE, true);
  delay(500);
  stop();
  for (int i = 0; i < 3; i++) {
    seuils[i] =
      (capteur.calibrationOn.minimum[i] + capteur.calibrationOn.maximum[i]) / 2;
  }
}

void suivreLigne(QTRSensors &capteur) {
  uint16_t sensor[NB_CAPTEURS];
  int16_t position = capteur.readLineBlack(sensor);

  if (sensor[1] > seuils[1] && sensor[0] < seuils[0] && sensor[2] < seuils[2]) {

    moteurs(CRUISE, true);
  } else {
    erreur = position - CENTRE;
    P = Kp * erreur;

    D = Kd * (erreur - ancienneErreur);
    correction = P + D;

    int16_t vitesseG = CRUISE_PID - correction;
    int16_t vitesseD = CRUISE_PID + correction;

    vitesseG = constrain(vitesseG, 0, MAX_CRUISE);
    vitesseD = constrain(vitesseD, 0, MAX_CRUISE);

    ancienneErreur = erreur;

    moteurGauche(vitesseG, true);
    moteurDroit(vitesseD, true);
  }
}
