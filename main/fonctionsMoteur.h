#ifndef FONCTION_MOTEUR_H
#define FONCTION_MOTEUR_H

#include <Arduino.h>
#include <stdint.h>

// Initialisation des moteurs
void initMoteur(int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D);

// Contrôle des moteurs
void vitesseMot(int16_t speedLeft, int16_t speedRight, bool forward,bool reverse);
void avancer(int16_t speedLeft, int16_t speedRight);
void reculer(int16_t speedLeft, int16_t speedRight);

// Arrêt
void arretMot();

// Mouvement simples
void gauche(int16_t puissance);
void droite(int16_t puissance);

// Oscillation (calibration)
void ossiler(int16_t intervalle);

#endif