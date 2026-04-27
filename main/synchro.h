#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <Arduino.h>
#include <QTRSensors.h>

// Initialisation globale
void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D);

// Calibration avec mouvement
void calibrage(QTRSensors &capteur);
void alignement (QTRSensors &capteur); //Se retrouver sur la ligne noir apres calibrage
bool casDepart (QTRSensors &capteur); //Cas ou il voit que du noir
bool toutBlanc (QTRSensors &capteur);

#endif