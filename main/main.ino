/*#include <QTRSensors.h>
#include "fonctionsCapteur.h"

QTRSensors capteur;//installer la librairie QTRSensors de Pololu (oui c'est le bon nom)

//Optimal sensing distance: 0.125" (3 mm)
//Maximum recommended sensing distance: 0.25" (6 mm)

uint16_t sensors[3];

int16_t position;
int16_t chemin;
int16_t leftMotorSpeed;
int16_t rightMotorSpeed;
int16_t base = 100;
int16_t correction;

void setup() {
    Serial.begin(9600);

    initCapteur(capteur);
    calibrerCapteur(capteur);
}

void loop() {
    position = lireLigne(capteur, sensors);

    if (estToutBlanc(sensors)) {
        // gestion du blanc plus tard
    }

    chemin = position - 1000;
    correction = chemin / 10;

    leftMotorSpeed  = base - correction;
    rightMotorSpeed = base + correction;

    leftMotorSpeed  = constrain(leftMotorSpeed, 0, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);
}*/

#include "fonctionsMoteur.h"

// À adapter selon ton câblage
#define M1_PWM 6
#define M1_DIR 7
#define M2_PWM 5
#define M2_DIR 4

void setup() {
    Serial.begin(9600);
    initMoteur(M1_PWM, M1_DIR, M2_PWM, M2_DIR);
}
//gauche et droit sont inversé
void loop() {
    Serial.println("Gauche seul");
    avancer(150, 0); // gauche seul
    delay(2000);

    Serial.println("Droite seul");
    avancer(0, 150); // droite seul
    delay (2000);

    arretMot();
    delay (2000);
    Serial.println("les deux");
    avancer(150, 110);
    delay(4000);
}

