#include <QTRSensors.h>
#include "synchro.h"
#include "fonctionsCapteur.h"
#include "fonctionsMoteur.h"

#define M1_PWM 6
#define M1_DIR 7
#define M2_PWM 5
#define M2_DIR 4
#define nb_cptr 3
#define PIN_CAPTEURS {2,3,8}//change le pin du capteur 4 a 8 pour pas de conflit avec le pin de dir du moteur 2

const int CRUISE1 = 120;
const int CRUISE2 = 124;

QTRSensors capteur;//installer la librairie QTRSensors de Pololu (oui c'est le bon nom)
//Optimal sensing distance: 0.125" (3 mm)
//Maximum recommended sensing distance: 0.25" (6 mm)
//on met le capteur comme digital
//set


//on met
void setup() {
    Serial.begin(9600);
    uint8_t pinsCapteurs[] = PIN_CAPTEURS;
    initialisation(capteur,pinsCapteurs, nb_cptr,M1_PWM,M1_DIR,M2_PWM,M2_DIR);
    //Calibrage du capteur
    delay(3000);

    calibrage(capteur);

}

void loop() {
    //suivreLigne(capteur);
    //QTRType typeCapteur = capteur.getType();
    /*if(typeCapteur == QTRType::RC){
        Serial.println("Capteur est RC(digital)");
    } else if(typeCapteur == QTRType::Analog){
        Serial.println("Capteur est analogique");
    }*/
    /*uint16_t sensorsCali[nb_cptr];
    capteur.readCalibrated(sensorsCali);

    for (int i = 0; i < nb_cptr; i++) {
        Serial.print(sensorsCali[i]);
        Serial.print(" ");
    }
    Serial.println();
    delay(500);*/

    //avancer(CRUISE1,CRUISE2);
    suivreLigne(capteur);
    
}

