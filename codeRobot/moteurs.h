#ifndef MOTEURS_H
#define MOTEURS_H

#include <Arduino.h>
#include <stdint.h>

void initialisationMoteur(int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D);

void moteurGauche(int16_t vitesse, bool avancer);
void moteurDroit(int16_t vitesse, bool avancer);

void moteurs (int16_t vitesse, bool avancer);

void stop ();

//void ossiler();


#endif