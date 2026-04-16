#include <Arduino.h>

const int M1_PWM = 6;
const int M1_DIR = 7;
const int M2_PWM = 5;
const int M2_DIR = 4;

const int CRUISE1 = 255;   // tune separately 6.57 v for the left motor
const int CRUISE2 = 255;  // tune separately
const int KICK = 160;     // startup kick
const int KICK_TIME = 150;

void setup() {
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);

  // Force everything off immediately
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);

  delay(200);
}

void motor1(int speedVal, bool forward) {
  digitalWrite(M1_DIR, forward ? HIGH : LOW);
  analogWrite(M1_PWM, speedVal);
}

void motor2(int speedVal, bool forward) {
  digitalWrite(M2_DIR, forward ? HIGH : LOW);
  analogWrite(M2_PWM, speedVal);
}

void stopMotors() {
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
}

void drive(bool forward, int s1, int s2) {
  // startup kick to overcome static friction
  motor1(KICK, forward);
  motor2(KICK, forward);
  delay(KICK_TIME);

  motor1(s1, forward);
  motor2(s2, forward);
}

void loop() {
  drive(true, CRUISE1, CRUISE2);
  delay(2000);

  stopMotors();
  delay(2000);

  drive(false, CRUISE1, CRUISE2);
  delay(2000);

  stopMotors();
  delay(2000);
}