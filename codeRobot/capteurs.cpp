#include "capteurs.h"
#include <Arduino.h>

static int16_t SEUIL_BLANC = 250;
static int16_t SEUIL_NOIR = 750;
//je suis bête, j'avais écrit initCapteur
void initialisationCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs) {
  //fonctions de la librairie
  capteur.setTypeRC();
  capteur.setSensorPins(pins, nbCapteurs);
}

int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]) {
  return capteur.readLineBlack(sensors);
}

bool outOfBounds(QTRSensors &capteur, uint16_t sensors[]){
  capteur.readCalibrated(sensors); 
  return sensors[0]<SEUIL_BLANC && sensors[1]<SEUIL_BLANC && sensors[2]<SEUIL_BLANC;
}

bool allBlack(QTRSensors &capteur, uint16_t sensors[]){
  capteur.readCalibrated(sensors);
  return sensors[0]>SEUIL_NOIR && sensors[1]>SEUIL_NOIR&& sensors[2]>SEUIL_NOIR;
}

bool onLine (QTRSensors &capteur, uint16_t sensors[]){
  capteur.readCalibrated(sensors);
  return sensors[0]<SEUIL_BLANC && sensors[1]>SEUIL_NOIR&& sensors[2]<SEUIL_BLANC;

}