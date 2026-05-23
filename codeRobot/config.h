#ifndef CONFIG_H
#define CONFIG_H

#include <QTRSensors.h>
#include <Arduino.h>

// ===== MOTEURS =====

#define M1_PWM 5
#define M1_DIR 4

#define M2_PWM 6
#define M2_DIR 7

// ===== CAPTEURS =====

#define NB_CAPTEURS 3

const uint8_t capteursPins[NB_CAPTEURS] = {2,3,4};

// ===== PID =====

extern int vitesseBase;
extern int vitesseMax;

extern float Kp;
extern float Ki;
extern float Kd;

#endif