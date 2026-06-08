#ifndef SUIVEUR_H
#define SUIVEUR_H

#include <Arduino.h>
#include <QTRSensors.h>

void initialisation (QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D);

void calibrage(QTRSensors &capteur);
void allignement (QTRSensors &capteur);
void suivreLigne (QTRSensors &capteur);//fonction principale pour le suivie de ligne



#endif