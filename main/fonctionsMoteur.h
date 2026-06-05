#ifndef FONCTION_MOTEUR_H
#define FONCTION_MOTEUR_H

#include <Arduino.h>
#include <stdint.h>

// Initialisation des moteurs
void initMoteur(int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D);

// Contrôle des moteurs
void vitesseMot(int16_t speedLeft, int16_t speedRight, bool forward1,bool forward2);
void avancer(int16_t speed); //apres un stop pour demarrer les moteurs en meme temps
void reculer(int16_t speed);

// Arrêt
void arretMot();

// Mouvement simples puissance sur 2 moteurs
void gauche(int16_t puissance);
void droite(int16_t puissance);

// Oscillation (calibration)
void ossiler();

#endif