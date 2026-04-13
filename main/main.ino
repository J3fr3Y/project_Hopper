#include <QTRSensors.h>
#include "fonctionsCapteur.h"

QTRSensors capteur ; //installer la librairie QTRSensors de Pololu (oui c'est le bon nom)

uint16_t sensors[3];
int16_t position;
int16_t chemin; 
int16_t leftMotorSpeed; 
int16_t rightMotorSpeed; 
int16_t base = 100;
int16_t correction;
//Optimal sensing distance: 0.125" (3 mm)
//Maximum recommended sensing distance: 0.25" (6 mm)

void setup (){
    Serial.begin (9600);

    initCapteur(capteur);
    calibrerCapteur(capteur);
}

void loop (){

    position = lireLigne(capteur, sensors);

    /*Serial.print("S: ");
    Serial.print(sensors[0]);
    Serial.print(" ");
    Serial.print(sensors[1]);
    Serial.print(" ");
    Serial.println(sensors[2]);*/

    if (estToutBlanc(sensors)){
        // gestion du blanc plus tard
    }
    
    chemin = position -1000;
    correction = chemin/10; //pour adoucir les virages
    leftMotorSpeed = rightMotorSpeed =base;

    leftMotorSpeed  = base - correction;
    rightMotorSpeed = base + correction;
    leftMotorSpeed  = constrain(leftMotorSpeed, 0, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);


}