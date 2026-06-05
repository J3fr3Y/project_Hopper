#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 90

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

  initialisationCapteur(capteur, pinsCapteurs, nbCapteurs);
  initialisationMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage (QTRSensors &capteur){
  moteurs(CRUISE, false); 
  delay (200);
  stop();
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();//Fonction de la librairie
    // mouvement pendant calibration
    delay(20);
  }
  moteurs(CRUISE, true); 
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
    moteurs(CRUISE,avancer);
  }
  stop();

}