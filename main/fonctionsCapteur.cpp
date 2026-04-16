#include "fonctionsCapteur.h"

// Pins fixées ici (comme dans ton code)
static const uint8_t pins[NB_CAPTEURS] = {2, 3, 4};

void initCapteur(QTRSensors &capteur) {
    capteur.setTypeRC();
    capteur.setSensorPins(pins, NB_CAPTEURS);
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

bool estToutBlanc(uint16_t sensors[]) {
    return (sensors[0] < 750 &&
            sensors[1] < 750 &&
            sensors[2] < 750);
}