#include "QTRSensors.h"
#include "synchro.h"
#include "fonctionsCapteur.h"
#include "fonctionsMoteur.h"

#define CENTRE 1000 // car centre = (nbCapteur -1)*1000 /2
#define SEUIL 50 // ENTRE 30 ET 100 depend du capteur cest pour une marge de tolerance pour l'alignement
#define K 100 //Facteur a regler pour le calcul de correction [90,120] mouvement doux
#define nb_cptr 3
#define SEUIL_NOIR 700 //seuil pourdire qu on voit du noir [600,800] 
#define SEUIL_BLANC 250 //seuil pourdire qu on voit du blanc [100,300] 

const int CRUISE1 = 120;
const int CRUISE2 = 124;

void initialisation(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

    initCapteur(capteur, pinsCapteurs, nbCapteurs);
    initMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrage(QTRSensors &capteur) {
    Serial.println("Calibrage dynamique...");

    for (uint8_t i = 0; i < 200; i++) {
        capteur.calibrate();//Fonction de la librairie
        ossiler(); // mouvement pendant calibration
        delay(20);
    }

    arretMot();

    Serial.println("Fin calibrage");
}

void alignement (QTRSensors &capteur){
    uint16_t sensor[nb_cptr];
    int16_t position = capteur.readLineBlack(sensor);
    int16_t erreur = 0;
    while (1) {
        position = capteur.readLineBlack(sensor); 
        erreur = position -CENTRE;

        if (erreur>SEUIL){ // ligne à droite → pivoter à gauche
            gauche(K);
        }else if (erreur<-SEUIL){// ligne à gauche → pivoter à droite
            droite(K);
        }else{
            arretMot();
            break;
        }
    }
}

bool casDepart (QTRSensors &capteur){
    uint16_t sensor[nb_cptr];
    capteur.read(sensor);

    int16_t compteur = 0;

    for (int16_t i =0; i<nb_cptr; i++) {
        if (sensor[i]<SEUIL_NOIR){ //Seuil a tester
            return false; // Si un des capteurs vois du blanc
        }
    }
    return true;

}

bool toutNoir (QTRSensors &capteur){
    uint16_t sensor[nb_cptr];
    capteur.readCalibrated(sensor);

    int16_t compteur = 0;

    for (int16_t i =0; i<nb_cptr; i++) {
        if (sensor[i]<SEUIL_NOIR){ //Seuil a tester
            return false; // Si un des capteurs vois du blanc
        }
    }
    return true;

}

bool toutBlanc (QTRSensors &capteur){
    uint16_t sensor[nb_cptr];
    capteur.readCalibrated(sensor);

    int16_t compteur = 0;

    for (int16_t i =0; i<nb_cptr; i++) {
        if (sensor[i]>SEUIL_BLANC){ //Seuil a tester
            return false; // Si un des capteurs voit du noir
        }
    }
    return true;
}

void suivreLigne (QTRSensors &capteur){
    uint16_t sensor[nb_cptr];
    int16_t position = capteur.readLineBlack(sensor);
    if (toutBlanc(capteur)||toutNoir(capteur)){
        arretMot();
        return;
    }
    int16_t vitesse1;
    int16_t vitesse2;
    int16_t erreur = position -CENTRE;
    if (abs(erreur)<SEUIL){
        vitesse1 = CRUISE1;
        vitesse2 = CRUISE2;
    }else {
        int16_t correction = erreur/K;
        vitesse1 = CRUISE1-correction;
        vitesse2 = CRUISE2+correction;
    }

    vitesseMot(constrain(vitesse1,90,190),constrain(vitesse2,90,190),true,true);    

}







