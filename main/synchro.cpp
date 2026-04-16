#include <stdint.h>
#include "./fonctionsCapteur.h"
#include "./fonctionsMoteur.h"
#include "synchro.h"

void initialisation(int16_t S1, int16_t S2, int16_t S3, int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D, QTRSensors &capteur){
  int16_t Sens1 = S1; 
  int16_t Sens2 = S2;
  int16_t Sens3 = S3; 
  int16_t M1_PWR = M1_P;
  int16_t M1_DIR = M1_D;
  int16_t M2_PWR = M2_P; 
  int16_t M2_DIR = M2_D;
  
  initMoteur(M1_PWR, M1_DIR, M2_PWR, M2_DIR);
  initCapteur(capteur);
}

void calibrage(int &capteur){
  int16_t r = 0
    Serial.println("Calibrage...");

  for (uint8_t i = 0; i < 200; i++) {
      capteur.calibrate();
      delay(20);
      if (i == 24+r){
        //bouge
        r+=25;
      }
      
  }

  Serial.println("Fin calibrage");
}