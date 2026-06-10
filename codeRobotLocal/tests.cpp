#include "HardwareSerial.h"
#include "tests.h"
#include "capteurs.h"
#include "moteurs.h"
#include <Arduino.h>

#define NB_CAPTEURS 3
#define CRUISE 90 
#define CRUISE_PID 75 //last ideal speed 72
#define CRUISE_CALIBRATE 110
#define MAX_CRUISE 250
#define CENTRE 1000

int16_t erreurTest;
int16_t ancienneErreurTest = 0;
float KpTest = 0.35;//last ideal kp = 0.35
float KdTest = 2.8;//last ideal kd = 3.5
float correctionTest;
float PTest; 
float DTest;

int16_t seuilsTest[NB_CAPTEURS];

void initialisationTest(QTRSensors &capteur,
                    uint8_t pinsCapteurs[], uint8_t nbCapteurs,
                    int16_t M1_P, int16_t M1_D,
                    int16_t M2_P, int16_t M2_D) {

  initialisationCapteur(capteur, pinsCapteurs, nbCapteurs);
  initialisationMoteur(M1_P, M1_D, M2_P, M2_D);
}

void calibrageTest(QTRSensors &capteur){
  Serial.print("Debut calibrage");
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();//Fonction de la librairie
    // mouvement pendant calibration
    delay(20);
  }
  Serial.print("Move bitch ! ");
  delay(1000);
  for (uint8_t i = 0; i < 100; i++) {
    capteur.calibrate();//Fonction de la librairie
    // mouvement pendant calibration
    delay(20);
  }
  Serial.print("fin calibrage");
  delay(2000);

  for (int i = 0; i < 3; i++) {
    seuilsTest[i] =
        (capteur.calibrationOn.minimum[i] +
         capteur.calibrationOn.maximum[i]) / 2;
  }
  for (int i = 0; i < 3; i++) {
    Serial.print("Capteur ");
    Serial.print(i);

    Serial.print(" Min = ");
    Serial.print(capteur.calibrationOn.minimum[i]);

    Serial.print(" Max = ");
    Serial.println(capteur.calibrationOn.maximum[i]);
  } 

}


void suivreLigneTest (QTRSensors &capteur){
  uint16_t sensorTest[NB_CAPTEURS];
  int16_t positionTest = capteur.readLineBlack(sensorTest);
    erreurTest = positionTest - CENTRE;
    PTest = KpTest*erreurTest; 

    DTest = KdTest *(erreurTest-ancienneErreurTest);
    correctionTest = PTest+DTest; 

    int16_t vitesseGTest = CRUISE_PID - correctionTest;
    int16_t vitesseDTest = CRUISE_PID + correctionTest;

    vitesseGTest = constrain(vitesseGTest, 0, MAX_CRUISE);
    vitesseDTest = constrain(vitesseDTest, 0, MAX_CRUISE);
  
    Serial.print(positionTest);
    Serial.print("\t");
    Serial.print(erreurTest);
    Serial.print("\t");
        Serial.print(PTest);
    Serial.print("\t");
    Serial.print(DTest);
    Serial.print("\t");
    Serial.print(vitesseGTest);
    Serial.print("\t");
    Serial.println(vitesseDTest);

    ancienneErreurTest = erreurTest;


  
}








