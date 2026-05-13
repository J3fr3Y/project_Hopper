#include <QTRSensors.h>
#include "synchro.h"
#include "fonctionsCapteur.h"
#include "fonctionsMoteur.h"

#define M1_PWM 6
#define M1_DIR 7
#define M2_PWM 5
#define M2_DIR 4
#define nb_cptr 3
#define PIN_CAPTEURS {2,3,4}

const int CRUISE1 = 120;
const int CRUISE2 = 124;

QTRSensors capteur;//installer la librairie QTRSensors de Pololu (oui c'est le bon nom)
//Optimal sensing distance: 0.125" (3 mm)
//Maximum recommended sensing distance: 0.25" (6 mm)

void setup() {
    Serial.begin(9600);
    uint8_t pinsCapteurs[] = PIN_CAPTEURS;
    initialisation(capteur,pinsCapteurs, nb_cptr,M1_PWM,M1_DIR,M2_PWM,M2_DIR);
    //Calibrage du capteur
    delay(3000);
    while(casDepart(capteur)){
        vitesseMot(CRUISE1, CRUISE2, true, true);
        delay(50);
        arretMot();
    }
    calibrage(capteur);

}

void loop() {
    suivreLigne(capteur);

    /*uint16_t sensorsCali[nb_cptr];
    capteur.readCalibrated(sensorsCali);

    for (int i = 0; i < nb_cptr; i++) {
        Serial.print(sensorsCali[i]);
        Serial.print(" ");
    }
    Serial.println();
    delay(500);*/

    //avancer(CRUISE1,CRUISE2);

    
}

