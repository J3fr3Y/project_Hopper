#include <QTRSensors.h>
#include <Arduino.h>
#include "suiveur.h"
#include "capteurs.h"
#include "moteurs.h"
#include "tests.h"

#define M1_PWM 6
#define M1_DIR 7
#define M2_PWM 5
#define M2_DIR 4
#define nb_cptr 3
#define PIN_CAPTEURS {2,3,8}
#define KICK 110
QTRSensors capteur;
bool started = false;
uint16_t sensor[3];


void setup() {
  Serial.begin(9600);
  uint8_t pinsCapteurs[] = PIN_CAPTEURS;
  initialisation(capteur,pinsCapteurs, nb_cptr,M1_PWM,M1_DIR,M2_PWM,M2_DIR);
  delay(3000);
  calibrage(capteur);
  delay(1000);
}

void loop() {
  suivreLigne(capteur);
  //suivreLigneTest(capteur);

}

