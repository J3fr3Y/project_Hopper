#ifndef MOTEURS_H
#define MOTEURS_H
#include <Arduino.h>

void initMoteurs();

void moteurGauche(int vitesse);
void moteurDroit(int vitesse);

void avancer(int vitesse);
void tournerDroite(int vitesse);
void tournerGauche(int vitesse);

void stopMoteurs();

#endif