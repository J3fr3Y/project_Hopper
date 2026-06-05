#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 90
#define MAX_CRUISE 100
#define MIN_CRUISE 70
#define CENTRE 1000

int16_t erreur;
int16_t ancienneErreur = 0;
float Kp = 0.12;
float Kd = 0.25;
float correction;
int16_t P; 
int16_t D;

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

  initialisationCapteur(capteur, pinsCapteurs, nbCapteurs);
  initialisationMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage (QTRSensors &capteur){
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();//Fonction de la librairie
    // mouvement pendant calibration
    delay(20);
  }
  moteurs(CRUISE, false); 
  delay (200);
  stop();
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();//Fonction de la librairie
    // mouvement pendant calibration
    delay(20);
  }
}

void allignement (QTRSensors &capteur){
  uint16_t sensors [NB_CAPTEURS];
  bool avancer = true;
  while (!allBlack(capteur,sensors)){
    moteurs(CRUISE,avancer);
    delay(10);
    stop();
  }
}



void suivreLigne (QTRSensors &capteur){
  uint16_t sensor[NB_CAPTEURS];
  int16_t position = capteur.readLineBlack(sensor);
  erreur = position - CENTRE;
  P = Kp*erreur; 
  D = Kd *(erreur-ancienneErreur);
  correction = P +D; 

  ancienneErreur = erreur;

  int16_t vitesseG = CRUISE + correction;
  int16_t vitesseD = CRUISE -correction;

  moteurGauche(constrain(vitesseG,MIN_CRUISE,MAX_CRUISE), true);
  moteurDroit(constrain(vitesseD,MIN_CRUISE,MAX_CRUISE),true);

}








