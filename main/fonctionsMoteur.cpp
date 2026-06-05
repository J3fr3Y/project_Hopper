#include <stdint.h>
#include "Arduino.h"
#include "fonctionsMoteur.h"

// Variables internes au module (plus de dépendance externe)
static int16_t M1_PWM;
static int16_t M1_DIR;
static int16_t M2_PWM;
static int16_t M2_DIR;

//variable de vitesse des moteurs [0, 255]
//ecart de 4 entre le moteur gauche(-4) et droit 

const int CRUISE1 = 120;
const int CRUISE2 = 124;
const int KICK = 160;
const int KICK_TIME = 50;
const int CRUISE_CALIBRATE = 90;
const int intervalle = 10;//Utilisee dans ossiler

enum Direction {
    GAUCHE,
    DROITE
};
Direction dir = GAUCHE;
int16_t compteur = 5;

//Initialisation
void initMoteur(int16_t m1_pwm, int16_t m1_dir, int16_t m2_pwm, int16_t m2_dir) {

    // Stockage des pins
    M1_PWM = m1_pwm;
    M1_DIR = m1_dir;
    M2_PWM = m2_pwm;
    M2_DIR = m2_dir;

    pinMode(M1_PWM, OUTPUT);
    pinMode(M1_DIR, OUTPUT);
    pinMode(M2_PWM, OUTPUT);
    pinMode(M2_DIR, OUTPUT);

    // État initial
    digitalWrite(M1_DIR, LOW);
    digitalWrite(M2_DIR, LOW);
    arretMot();
}

//Changer la vitesse des Moteurs Valeur pour les 2 moteurs separement et un boolean pour savoir dans quel sens tourner
void vitesseMot(int16_t speed1, int16_t speed2, bool forwardM1, bool forwardM2) {

    digitalWrite(M1_DIR, forwardM1 ? HIGH : LOW);
    digitalWrite(M2_DIR, forwardM2 ? HIGH : LOW);

    analogWrite(M1_PWM, speed1);
    analogWrite(M2_PWM, speed2);
}


//Arret des moteurs
void arretMot() {
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
}

//tourner a gauche avec les 2 roues
void gauche(int16_t puissance) {
    vitesseMot(puissance, puissance,false, true);

}
//Tourner a droite avec les 2 roues
void droite(int16_t puissance) {
    vitesseMot(puissance, puissance, true,false);
}

//Pour demarrer les moteurs en meme temps (a utiliser apres un arretMot())
void avancer(int16_t speed) {
    // Kick initial
    vitesseMot(KICK, KICK, true,true);
    delay(KICK_TIME);

    // Vitesse normale
    vitesseMot(speed, speed, true, true);
}

//Pour reculer
void reculer(int16_t speed) {
    vitesseMot(speed, speed, false,false);
}

//pour ossiler pendant le cablibrage (intervalle pour savoir quand changer de direction)
void ossiler() {
    //static int16_t compteur = 0;
    //static Direction dir = GAUCHE;

    if (dir == GAUCHE) {
        gauche(CRUISE_CALIBRATE);
    } else {
        droite(CRUISE_CALIBRATE);
    }

    compteur++;

    if (compteur >= intervalle) {
        dir = (Direction)!dir;
        compteur = 0;
    }
}