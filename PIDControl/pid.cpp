#include <Arduino.h>
#include "pid.hpp"

PID::PID(){
  this->reference = LOW_LUX;
  this->Ki = KI;
  this->Kp = KP;
  this->K2 = KP*KI*TS/2.0;
}

void PID::SetKi(double p){
  this->Ki = p;
}
void PID::SetKp(double i){
  this->Kp = i;
}
void PID::UpdateK2(){
  this->K2 = (this->Kp)*(this->Ki)*TS/2.0;
}

void PID::SetRef(double ref){
  this->reference = ref;
}

double PID::GetKi(){
  return this->Ki;
}
    
double PID::GetKp(){
  return this->Kp;
}
    
double PID::GetK2(){
  return this->K2;
}

double PID::GetRef(){
  return this->reference;
}

void PID::LightSwitch(){
  if(this->reference == HIGH_LUX){
    this->reference = LOW_LUX;
  }else{
    this->reference = HIGH_LUX;
  }
}

double PID::DeadZone(double y){
  double error = (this->reference) - y;
  if(error >= ERROR_MAX){
    return error - ERROR_MAX;
  }else if(error <= ERROR_MIN){
    return error + ERROR_MIN; 
  }
  return 0;  
}

int PID::PmwLimiter(int pmw){
  if(pmw >= 255){
    return 255;
  }else if(pmw <= 0){
    return 0; 
  }
  return pmw;  
}

int PID::AntiWindup(int u, int u_sat){
   return KS*(u_sat-u);
}

int PID::AnalogReadAvg(int pin, int n){
  int counter, avg = 0;
  for(counter=0; counter<n; counter++)
    avg += analogRead(pin); 
  return avg/n;
}

double PID::FeedForward(){
  return (this->reference)*KF;
}

double PID::ProportionalControl(double error){
  return ((this->Kp)*error);  
}

double PID::IntegralControl(double integral, double err, double prev_err){
  return integral + ((this->K2)*(err+prev_err));
}

double PID::DerivativeControl(){
  return 0.0;  
}
