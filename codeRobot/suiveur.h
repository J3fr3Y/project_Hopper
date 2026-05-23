#ifndef SUIVEUR_H
#define SUIVEUR_H
#include <Arduino.h>
#include <QTRSensors.h>

// ===== VARIABLES PID =====

extern int vitesseBase;
extern int vitesseMax;

extern float Kp;
extern float Ki;
extern float Kd;

extern int erreurPrecedente;
extern float sommeErreurs;


// ===== FONCTIONS =====

void suivreLigne();

int calculCorrectionPID(int erreur);

int limiterVitesse(int vitesse);

// Cas particuliers
void rechercheLigne();

void gererIntersection();

void gererArrivee();

void gestionDepart();

#endif