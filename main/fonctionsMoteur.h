#include <stdint.h>
#ifndef FONCTION_MOTEUR_H
#define FONCTION_MOTEUR_H

#include <Arduino.h>

void initMoteur(int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D);
void vitesseMot(int16_t speed, bool forward);
void arretMot ();



#endif