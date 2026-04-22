#include "synchro.h"
#include "fonctionsCapteur.h"
#include "fonctionsMoteur.h"

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

    initCapteur(capteur, pinsCapteurs, nbCapteurs);
    initMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage(QTRSensors &capteur) {
    Serial.println("Calibrage dynamique...");

    for (uint8_t i = 0; i < 200; i++) {
        capteur.calibrate();
        ossiler(30); // mouvement pendant calibration
        delay(20);
    }

    arretMot();

    Serial.println("Fin calibrage");
}