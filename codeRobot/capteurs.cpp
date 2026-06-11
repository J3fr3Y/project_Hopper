#include "capteurs.h"
#include <Arduino.h>

static int16_t SEUIL_BLANC = 250;
static int16_t SEUIL_NOIR = 750;
static int16_t LIGNE_GAUCHE = 600;
static int16_t LIGNE_DROITE = 1400;

void initialisationCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs) {
  //fonctions de la librairie
  capteur.setTypeRC();
  capteur.setSensorPins(pins, nbCapteurs);
}

int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]) {
  return capteur.readLineBlack(sensors);
}

bool allWhite(QTRSensors &capteur, uint16_t sensors[]){
  capteur.readLineBlack(sensors); 
  return sensors[0]<SEUIL_BLANC && sensors[1]<SEUIL_BLANC && sensors[2]<SEUIL_BLANC;
}

bool allBlack(QTRSensors &capteur, uint16_t sensors[]){
  capteur.readLineBlack(sensors);
  return sensors[0]>SEUIL_NOIR && sensors[1]>SEUIL_NOIR && sensors[2]>SEUIL_NOIR;
}

bool onLine (QTRSensors &capteur, uint16_t sensors[]){
  int16_t position = capteur.readLineBlack(sensors);
  return position>LIGNE_GAUCHE && position<LIGNE_DROITE;
}

bool lineLeft (QTRSensors &capteur, uint16_t sensors[]){

  return capteur.readLineBlack(sensors)<LIGNE_GAUCHE;
}
bool lineRight (QTRSensors &capteur, uint16_t sensors[]){
  return capteur.readLineBlack(sensors)>LIGNE_DROITE;
}







