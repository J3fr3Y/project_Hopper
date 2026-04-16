#include <stdint.h>
#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <Arduino.h>
#include <QTRSensors>
#include "fonctionsCapteur.h"
#include "fonctionsMoteur.h"




void initialisation(int16_t S1,int16_t S2, int16_t S3, int16_t M1_P, int16_t M1_D, int16_t M2_P, int16_t M2_D, QTRSensors &capteur);
void calibrage (QTRSensors &capteur);
void ligneNoir();
void ligneBlanche();
void debutEnT();




#endif