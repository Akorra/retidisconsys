#include <Arduino.h>
#include "pid.hpp"

PID::PID(){
  this->K0 = 2.124;
  this->reference = 22;
  this->wait = 30;
  this->present = 0;
  this->previous = millis()-wait;
  this->response = 0;
}


PID::PID(double K, int ref, unsigned long w8){
  this->K0 = K;
  this->reference = ref;
  this->wait = w8;
  this->present = 0;
  this->previous = millis()-wait;
  this->response = 0;
}

bool PID::FeedForward(double y, const int LedPin){
  present = millis();
  if(present - previous >= wait){
    response = K0*reference;
    response = (response > 255) ? 255 : response;
    response = (response < 0) ? 0 : response;
    Serial.print("Error: ");
    Serial.println(reference - y);
    analogWrite(LedPin, response);
    previous = present;
    return true; 
  }else{
    return false;
  }
}

void PID::SetReference(int ref){ this->reference = ref; }
void PID::SetTimeConst(unsigned long w8){ this->wait = w8; }
void PID::SetGainConst(double K){ this->K0 = K; }
void PID::GetReference(){ Serial.println(this->reference); }
