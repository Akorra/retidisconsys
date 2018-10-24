#include "defs.hpp"

unsigned long starTime = 0;
int sensorValue = 0;
int stoploop = 1;
double sensorVoltage = 0;
double sensorLux = 0;
double ledVoltage = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  Serial.begin(230400);
  Serial.println("\nTimestamp,LED,Vi,Vo,LUX");
}

void loop() {
  if(stoploop){
    for(int i=0; i<=250; i+=10){
      analogWrite(10, i);
      starTime = micros();
      while(micros()-starTime < 500000){
        ledVoltage = (double)i*(5.0/255.0);
        sensorValue = analogRead(0);
        sensorVoltage = (double) Defs::raw2volt(sensorValue);
        sensorLux = Defs::volt2lux(sensorVoltage);
      
        Serial.print(micros());
        Serial.print(",");
        Serial.print(i);
        Serial.print(",");
        Serial.print((double)ledVoltage, 5);
        Serial.print(",");
        Serial.print((double)sensorVoltage, 5);
        Serial.print(",");
        Serial.print((double)sensorLux, 5);
        Serial.println();
        delay(5); /*5 ms sampling rate*/
      }  
    }
    stoploop = 0;
    Serial.println("FINISHED STEP RESPONSES");
  }
}
