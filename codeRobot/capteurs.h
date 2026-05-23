#ifndef CAPTEURS_H
#define CAPTEURS_H:
#include <Arduino.h>
#include <QTRSensors.h>


void initCapteurs();

void calibrationCapteurs();

uint16_t lirePosition();

bool lignePerdue();

void afficherCapteurs();

#endif