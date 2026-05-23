#include "config.h"
#include "moteurs.h"
#include "capteurs.h"
#include "suiveur.h"
#include "tests.h"
#include <Arduino.h>

void setup() {

  Serial.begin(9600);

  initMoteurs();

  initCapteurs();

  calibrationCapteurs();
}

void loop() {

  //suivreLigne();

  testCapteurs();
  //testMoteurs(); OK

}