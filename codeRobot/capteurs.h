#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <Arduino.h>
#include <QTRSensors.h>

void initialisationCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs); 
int16_t lireLigne (QTRSensors &capteur, uint16_t sensors[]);
bool outOfBounds (QTRSensors &capteur, uint16_t sensors[]);
bool allBlack(QTRSensors &capteur, uint16_t sensors[]);
bool onLine (QTRSensors &capteur, uint16_t sensors[]);



#endif