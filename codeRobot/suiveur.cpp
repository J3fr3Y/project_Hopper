#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 70
#define CRUISE_CALIBRATE 90
#define MAX_CRUISE 95
#define CENTRE 1000

int16_t erreur;
int16_t ancienneErreur = 0;
float Kp = 0.25;
float Ki = 0;
float Kd = 1.27;
float correction;
int16_t P; 
int16_t D;
int16_t I;
int16_t integrale = 0;

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
  moteurs(CRUISE_CALIBRATE, false); 
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
  bool avancer;
  if (outOfBounds(capteur,sensors)){
    avancer = true;
  }else if (onLine(capteur,sensors)){
    avancer = false; 
  }
  while (!allBlack(capteur,sensors)){
    moteurs(CRUISE_CALIBRATE,avancer);
    delay(10);
    stop();
  }
}



void suivreLigne (QTRSensors &capteur){
  uint16_t sensor[NB_CAPTEURS];
  //Nouvelle meusure
  int16_t position = capteur.readLineBlack(sensor);
  /*if (allBlack(capteur, sensor)){
    stop();
    delay(10000);
  }*/

  //Calcul de P
  erreur = position - CENTRE;
  P = Kp*erreur; 

  //Calcul de I
  integrale = integrale + erreur;
  I = integrale * Ki;


  D = Kd *(erreur-ancienneErreur);
  correction = P+I+D; 

  ancienneErreur = erreur;

  int16_t vitesseG = CRUISE + correction;
  int16_t vitesseD = CRUISE -correction;


  moteurGauche(vitesseG, true);
  moteurDroit(vitesseD,true);

}








