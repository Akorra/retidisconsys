#include "pid.hpp"
#include "defs.hpp"
#define LED 10
#define LDR 0

int sensorValue=0;
double sensorVoltage=0;
double sensorLux=0;

unsigned long startime;
unsigned long w8 = 30;

PID pid(2.124, 22, 30);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  pid.GetReference();
}

void loop() {
  // put your main code here, to run repeatedly:
  startime = millis();
  sensorValue = analogRead(LDR);
  sensorVoltage = (double) sensorValue*5.0/1023.0;
  sensorLux = Defs::volt2lux(sensorVoltage);
  pid.FeedForward(sensorLux, LED);
  delay(w8 - (millis() - startime));
}
