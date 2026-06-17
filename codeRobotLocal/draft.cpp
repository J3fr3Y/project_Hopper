/*#include "HardwareSerial.h"
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

#define CRUISE_MIN 45
#define CRUISE_MAX 170

#define ZONE_MORTE 30  //
#define CORRECTION_MAX 80 //70
#define ERREUR_FORTE 500 //
#define CRUISE_FAST 105
#define CRUISE_SLOW 85

#define BLANC 300
#define NOIR 700

int16_t erreur;
int16_t ancienneErreur ;
float Kp = 0.35;  //last ideal kp = 0.35 0.5
float Kd = 2.8;   //last ideal kd = 2.8 
float Ki = 0.001;
float correction;
float P;
float D;
float I;
float integrale;
int16_t seuils[NB_CAPTEURS];

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
  delay(600);
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
}

void suivreLigne(QTRSensors &capteur) {
  uint16_t sensor[NB_CAPTEURS];
  int16_t position = capteur.readLineBlack(sensor);

  erreur = position - CENTRE;
  int16_t absErreur = abs(erreur);
  
  bool gaucheNoir = sensor[0] > seuils[0];
  bool centreNoir = sensor[1] > seuils[1];
  bool droiteNoir = sensor[2] > seuils[2];

  bool gaucheBlanc = sensor[0] < seuils[0];
  bool centreBlanc = sensor[1] < seuils[1];
  bool droiteBlanc = sensor[2] < seuils[2];
  

  // Vitesse de base adaptative :
  // si l'erreur est grande, on ralentit pour mieux tourner
  int16_t baseSpeed;

  if (absErreur > ERREUR_FORTE) {
    baseSpeed = CRUISE_SLOW;
  } else {
    baseSpeed = CRUISE_FAST;
  }


  /* if (sensor[1] > seuils[1] && sensor[0] < seuils[0] && sensor[2] < seuils[2]) {
    ancienneErreur = 0;
    moteurs(CRUISE, true);
  } else {*/
    
    //P = Kp * erreur;


    //integrale = integrale + erreur;
    //I = integrale * Ki;

    //D = Kd * (erreur - ancienneErreur);
    //correction = P + D ;//+I

    // Petite zone morte pour éviter les micro-corrections en ligne droite
    /*if (absErreur < ZONE_MORTE) {
      correction = 0;
    }*/

    // Limiter la correction pour éviter qu'une roue ne reçoit pas de valeurs  en desoous de 40
    /*correction = constrain(correction, -CORRECTION_MAX, CORRECTION_MAX);
    int16_t vitesseG = baseSpeed - correction;
    int16_t vitesseD = baseSpeed + correction ;

bool casExtreme = false;

// Cas important : ligne très à gauche
if (gaucheNoir && centreBlanc && droiteBlanc) {
  vitesseG = 0;
  vitesseD = CRUISE_MAX;
  casExtreme = true;
}

// Cas important : ligne très à droite
else if (gaucheBlanc && centreBlanc && droiteNoir) {
  vitesseG = CRUISE_MAX;
  vitesseD = 0;
  casExtreme = true;
}

// Cas : tout blanc, ligne perdue
else if (gaucheBlanc && centreBlanc && droiteBlanc) {
  if (ancienneErreur > 0) {
    vitesseG = 0;
    vitesseD = CRUISE_MAX;
  } else {
    vitesseG = CRUISE_MAX;
    vitesseD = 0;
  }

  casExtreme = true;
}

if(!casExtreme){
    vitesseG = constrain(vitesseG, CRUISE_MIN, CRUISE_MAX);
    vitesseD = constrain(vitesseD, CRUISE_MIN, CRUISE_MAX);
}
    ancienneErreur = erreur;

    moteurGauche(vitesseG, true);
    moteurDroit(vitesseD, true);
  //}
}
*/