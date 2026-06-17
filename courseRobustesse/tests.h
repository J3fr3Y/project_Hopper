#ifndef TESTS_H
#define TESTS_H

#include <Arduino.h>
#include <QTRSensors.h>

void initialisationTest (QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D);

void calibrageTest(QTRSensors &capteur);
void suivreLigneTest (QTRSensors &capteur);//fonction principale pour le suivie de ligne



#endif