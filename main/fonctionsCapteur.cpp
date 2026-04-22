#include "fonctionsCapteur.h"


static const uint8_t SEUIL = 100;

void initCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs) {
    capteur.setTypeRC();
    capteur.setSensorPins(pins, nbCapteurs);
}

void calibrerCapteur(QTRSensors &capteur) {
    Serial.println("Calibrage...");

    for (uint8_t i = 0; i < 200; i++) {
        capteur.calibrate();
        delay(20);
    }

    Serial.println("Fin calibrage");
}

int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]) {
    return capteur.readLineBlack(sensors);
}

bool estToutBlanc(uint16_t sensors[], QTRSensors &capteur, uint8_t nbCapteurs) {
    capteur.readCalibrated(sensors);

    for (uint8_t i = 0; i < nbCapteurs; i++) {
        if (sensors[i] > (capteur.calibrationOn.minimum[i] + SEUIL)) {
            return false;
        }
    }

    return true;
}