#include "defs.hpp"

#define LED 10
#define LDR A0
#define PMW_MIN 0
#define PMW_MAX 128

unsigned long timestamp;
int ldr;
double sensorVoltage = 0.0;
double sensorLux = 0.0;
double ledVoltage = 0.0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Timestamp,LUX,LDR,Vo,Vi,LED");

  analogWrite(LED, PMW_MIN);
  delay(1000); //discharge capacitor
}

void loop() {
  analogWrite(LED, PMW_MIN);
  timestamp = millis();
  while (millis() < timestamp + 20){
    ldr = analogRead(LDR);
    sensorVoltage = (double) Defs::raw2volt(ldr);
    sensorLux = Defs::volt2lux(sensorVoltage);
    
    Serial.print(micros());
    Serial.print(",");
    Serial.print((double) sensorLux, 1);
    Serial.print(",");
    Serial.print(ldr);
    Serial.print(",");
    Serial.print((double)sensorVoltage, 1);
    Serial.print(",");
    Serial.print((double)PMW_MIN*(5.0/255.0), 1);
    Serial.print(",");
    Serial.println(PMW_MIN);
  }

  analogWrite(LED, PMW_MAX);
  timestamp = millis();
  while (millis() < timestamp + 400){
    ldr = analogRead(LDR);
    sensorVoltage = (double) Defs::raw2volt(ldr);
    sensorLux = Defs::volt2lux(sensorVoltage);
    
    Serial.print(micros());
    Serial.print(",");
    Serial.print((double) sensorLux, 1);
    Serial.print(",");
    Serial.print(ldr);
    Serial.print(",");
    Serial.print((double)sensorVoltage, 1);
    Serial.print(",");
    Serial.print((double)PMW_MAX*(5.0/255.0), 1);
    Serial.print(",");
    Serial.println(PMW_MAX);
  }
  
  delay(1000000);
}
