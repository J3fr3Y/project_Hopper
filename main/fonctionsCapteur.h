#ifndef FONCTION_CAPTEUR_H
#define FONCTION_CAPTEUR_H

#include <Arduino.h>
#include <QTRSensors.h>


void initCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs);
void calibrerCapteur(QTRSensors &capteur);
int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]);
bool estToutBlanc(uint16_t sensors[], QTRSensors &capteur, uint8_t nbCapteurs);


#endif