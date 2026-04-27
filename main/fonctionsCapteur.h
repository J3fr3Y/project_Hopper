#ifndef FONCTION_CAPTEUR_H
#define FONCTION_CAPTEUR_H

#include <Arduino.h>
#include <QTRSensors.h>


void initCapteur(QTRSensors &capteur, uint8_t pins[], uint8_t nbCapteurs);//initialisation du capteur
void calibrerCapteur(QTRSensors &capteur);//Calibrer le capteur NON UTILISER on a la fonctions dans synchro*/
int16_t lireLigne(QTRSensors &capteur, uint16_t sensors[]);//retourne les valeurs lue par le capteur
bool estToutBlanc(uint16_t sensors[], QTRSensors &capteur, uint8_t nbCapteurs); //Cas ou on ne voit plus la ligne noir


#endif