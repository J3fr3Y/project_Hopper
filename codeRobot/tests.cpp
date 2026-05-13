#include "tests.h"
#include "moteurs.h"
#include "capteurs.h"

void testMoteurs() {

  avancer(120);

  delay(2000);

  stopMoteurs();
}

void testRotation() {

  tournerDroite(120);

  delay(1000);

  stopMoteurs();
}