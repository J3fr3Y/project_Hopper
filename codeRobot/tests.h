#ifndef TESTS_H
#define TESTS_H
#include <Arduino.h>

// ===== TESTS MOTEURS =====

void testAvance();

void testRecul();

void testRotationGauche();

void testRotationDroite();

void testMoteurs();


// ===== TESTS CAPTEURS =====

void testCapteurs();

void testPosition();

void testDetection();


// ===== TESTS SUIVEUR =====

void testPID();

void testSuiviLent();

void testSuiviRapide();


// ===== DEBUG =====

void debugComplet();

void debugEtat();

void debugPID();

#endif