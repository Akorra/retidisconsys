#include <avr/io.h>
#include <avr/interrupt.h>

#include "pid.hpp"
#include "defs.hpp"

#define LED 10
#define LDR 0

int sensorValue=0;
int u = 0;
int u_sat = 0;
double sensorVoltage=0;
double sensorLux=0;
double prev_sensorLux=0;
double feedforward=0;
double err = 0;
double prev_err = 0;
double p = 0;
double i = 0;
double d = 0;
double value;

bool antiWindup = true;
bool forward = true;
bool back = true;

unsigned long startime;
//unsigned long prevtime;
//unsigned long vartime;
unsigned long w8 = 30;

PID pid;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  pid.LightSwitch();
  Serial.println(pid.GetRef());
  analogWrite(LED, 100);
}

void loop() {
  startime = millis();   
  //if(startime-prevtime > w8){
    sensorValue = pid.AnalogReadAvg(LDR, 3);
    sensorVoltage = (double) sensorValue*5.0/1023.0;
    sensorLux = Defs::volt2lux(sensorVoltage);

    //FeedForward
    if(forward) feedforward = pid.FeedForward();
    
    //FeedBack
    if(back){
      err = pid.DeadZone(sensorLux);

      //print error
      Serial.print("; ");
      Serial.print("Error: ");
      Serial.println(err);
    
      p = pid.ProportionalControl(err);
      i = pid.IntegralControl(i, err, prev_err);
      if(antiWindup){
        i += pid.AntiWindup(u, u_sat);
      }
      d = pid.DerivativeControl(sensorLux, prev_sensorLux);
      u = round(p + i - d + feedforward);
      u_sat = pid.PmwLimiter(u);
      analogWrite(LED, u_sat);

      //print variables
      Serial.print("Kp: ");
      Serial.print((double) pid.GetKp());
      Serial.print("; ");
      Serial.print("Ref: ");
      Serial.print((double) pid.GetRef());
      Serial.print("; ");
      Serial.print("Out: ");
      Serial.print((double) sensorLux);
      Serial.print(" U: ");
      Serial.print(u_sat);
      
      prev_err = err;
      prev_sensorLux = sensorLux;
    }
    //prevtime = startime;
    delay(w8-(millis()-startime)); 
  //}
  
  //while (Serial.available()) {
  //  value = Serial.parseFloat();
  //  pid.SetKp(value);
  //  Serial.print("New Kp: ");
  //  Serial.println(value);
  //}
}
