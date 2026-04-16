#include <Arduino.h>
// DFRobot L293 Shield V1.1
// Motor 1: PWM D6, DIR D7
// Motor 2: PWM D5, DIR D4

const int M1_PWM = 6;
const int M1_DIR = 7;
const int M2_PWM = 5;
const int M2_DIR = 4;

void setup() {
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);

  Serial.begin(9600);
}

void motor1(int speedVal, bool forward) {
  digitalWrite(M1_DIR, forward ? HIGH : LOW);
  analogWrite(M1_PWM, speedVal);   // 0..255
}

void motor2(int speedVal, bool forward) {
  digitalWrite(M2_DIR, forward ? HIGH : LOW);
  analogWrite(M2_PWM, speedVal);   // 0..255
}

void stopMotors() {
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}

void loop() {
  Serial.println("Forward");
  motor1(90, true);
  motor2(90, true);
  delay(3000);

  Serial.println("Backward");
  motor1(90, false);
  motor2(90, false);
  delay(3000);

  Serial.println("Stop");
  stopMotors();
  delay(2000);
}