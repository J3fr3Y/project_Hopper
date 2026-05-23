#include "config.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

QTRSensors qtr;

uint16_t valeursCapteurs[NB_CAPTEURS];

void initCapteurs() {

  qtr.setTypeAnalog();

  qtr.setSensorPins(capteursPins, NB_CAPTEURS);
}
void afficherCapteurs() {

  qtr.read(valeursCapteurs);

  for (int i = 0; i < NB_CAPTEURS; i++) {

    Serial.print(valeursCapteurs[i]);
    Serial.print("\t");
  }

  Serial.println();
}

void calibrationCapteurs() {

  for (int i = 0; i < 300; i++) {

    qtr.calibrate();

    tournerDroite(80);

    delay(5);
  }

  stopMoteurs();
}

uint16_t lirePosition() {

  return qtr.readLineBlack(valeursCapteurs);
}

bool lignePerdue() {

  qtr.read(valeursCapteurs);

  return (
    valeursCapteurs[0] < 200 &&
    valeursCapteurs[1] < 200 &&
    valeursCapteurs[2] < 200
  );
}