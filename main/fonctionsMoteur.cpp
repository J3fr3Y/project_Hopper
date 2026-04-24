#include <stdint.h>
#include "Arduino.h"
#include "fonctionsMoteur.h"

// Variables internes au module (plus de dépendance externe)
static int16_t M1_PWM;
static int16_t M1_DIR;
static int16_t M2_PWM;
static int16_t M2_DIR;

const int CRUISE1 = 255;
const int CRUISE2 = 255;
const int KICK = 160;
const int KICK_TIME = 150;
const int CRUISE_CALIBRATE = 90;

enum Direction {
    GAUCHE,
    DROITE
};

void initMoteur(int16_t m1_pwm, int16_t m1_dir,
                int16_t m2_pwm, int16_t m2_dir) {

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
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
}

void vitesseMot(int16_t speed1, int16_t speed2, bool forward, bool reverse) {
    digitalWrite(M1_DIR, forward ? HIGH : LOW);
    digitalWrite(M2_DIR, reverse ? HIGH : LOW);

    analogWrite(M1_PWM, speed1);
    analogWrite(M2_PWM, speed2);
}

void arretMot() {
    analogWrite(M1_PWM, 0);
    analogWrite(M2_PWM, 0);
}

void gauche(int16_t puissance) {
    vitesseMot(puissance, puissance,false, true);

}

void droite(int16_t puissance) {
    vitesseMot(puissance, puissance, true,false);
}

void avancer(int16_t speedLeft, int16_t speedRight) {
    // Kick initial
    vitesseMot(200, 200, true,true);
    delay(100);

    // Vitesse normale
    vitesseMot(speedLeft, speedRight, true, true);
}

void reculer(int16_t speedLeft, int16_t speedRight) {
    vitesseMot(speedLeft, speedRight, false,false);
}

void ossiler(int16_t intervalle) {
    static int16_t compteur = 0;
    static Direction dir = GAUCHE;

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