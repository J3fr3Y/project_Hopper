#include "fonctionsCapteur.h"

static const uint8_t SEUIL = 100;//Utiliser comme limite pour detecter le blanc

void initCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs) {
    //fonctions de la librairie
    capteur.setTypeRC();
    capteur.setSensorPins(pins, nbCapteurs);
}
/* NON UTILISEE on l'a dans synchro */
//Il faut presenter toutes la valeurs au capteur 
void calibrerCapteur(QTRSensors &capteur) {
    Serial.println("Calibrage...");

    for (uint8_t i = 0; i < 200; i++) {
        capteur.calibrate();
        delay(20);
    }

    Serial.println("Fin calibrage");
}

//Utilisation de la libraire
//Donne la valeur lue pour chacun des capteurs dans sensors
int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]) {
    return capteur.readLineBlack(sensors);
}

// Cas ou on ne capte plus la ligne noir
bool estToutBlanc(uint16_t sensors[], QTRSensors &capteur, uint8_t nbCapteurs) {
    capteur.readCalibrated(sensors);

    for (uint8_t i = 0; i < nbCapteurs; i++) {
        if (sensors[i] > (capteur.calibrationOn.minimum[i] + SEUIL)) {
            return false;
        }
    }

    return true;
}