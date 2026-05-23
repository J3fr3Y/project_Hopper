#include "tests.h"
#include <Arduino.h>
#include <QTRSensors.h>
#include "moteurs.h"
#include "capteurs.h"
#include "suiveur.h"

void testAvance() {

  avancer(120);

  delay(2000);

  stopMoteurs();
}

void testRecul() {

  avancer(-120);

  delay(2000);

  stopMoteurs();
}

void testRotationGauche() {

  tournerGauche(120);

  delay(1000);

  stopMoteurs();
}

void testRotationDroite() {

  tournerDroite(120);

  delay(1000);

  stopMoteurs();
}

void testMoteurs() {

  testAvance();

  delay(1000);

  testRecul();

  delay(1000);

  testRotationGauche();

  delay(1000);

  testRotationDroite();
}

void testCapteurs() {

  afficherCapteurs();

  delay(100);
}

void testPosition() {

  int position = lirePosition();

  Serial.println(position);

  delay(100);
}

void testDetection() {

  if (lignePerdue()) {

    Serial.println("LIGNE PERDUE");

  } else {

    Serial.println("LIGNE DETECTEE");
  }

  delay(100);
}

void testPID() {

  suivreLigne();
}

void testSuiviLent() {

  vitesseBase = 70;

  suivreLigne();
}

void testSuiviRapide() {

  vitesseBase = 150;

  suivreLigne();
}

void debugComplet() {

  afficherCapteurs();

  testPosition();
}

void debugEtat() {

  if (lignePerdue()) {

    Serial.println("PERDU");

  } else {

    Serial.println("SUIVI");
  }
}

void debugPID() {

  Serial.print("Kp : ");
  Serial.println(Kp);

  Serial.print("Kd : ");
  Serial.println(Kd);
}