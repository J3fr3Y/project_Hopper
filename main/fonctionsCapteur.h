#ifndef FONCTION_CAPTEUR_H
#define FONCTION_CAPTEUR_H

#define NB_CAPTEURS 3

#include <Arduino.h>
#include <QTRSensors.h>


void initCapteur(QTRSensors &capteur);
void calibrerCapteur(QTRSensors &capteur);
int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]);
bool estToutBlanc(uint16_t sensors[]);

// Debug
void afficherCapteurs(uint16_t sensors[]);

#endif