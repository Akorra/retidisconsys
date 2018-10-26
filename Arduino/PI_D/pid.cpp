#include <Arduino.h>
#include "pid.hpp"

/**Class Constructor**/
PID::PID(){
  reference = LOW_LUX;  
  Ki = KI;
  Kp = KP;
  Ts = TS; 
  K2 = KP*KI*TS/2.0;
  K3 = KD/TS;
}

/***********************************************
 *  Setter Methods for PID Class
 ***********************************************/
void PID::SetKi(double gain){ Ki = gain; K2 = (Ki*Kp*Ts)/2.0; }
void PID::SetKp(double gain){ Kp = gain; K2 = (Ki*Kp*Ts)/2.0; }
void PID::SetKd(double gain){ Kd = gain; K3 = Kd/Ts; }
void PID::SetKf(double gain){ Kf = gain; }
void PID::SetRef(double ref){ reference = ref; }

/***********************************************
 *  Getter Methods for PID Class
 ***********************************************/
double PID::GetKi(){ return Ki; }
double PID::GetKp(){ return Kp; }
double PID::GetKd(){ return Kd; }
double PID::GetKf(){ return Kf; }
double PID::GetK2(){ return K2; }
double PID::GetK3(){ return K3; }
double PID::GetRef(){ return reference; }

/***********************************************
 *  LightSwitch
 *    - Toggles the LUX reference value between
 *      high and low to account for the presence
 *      of employees in the room
 ***********************************************/
void PID::LightSwitch(){
  if(reference == HIGH_LUX){
    reference = LOW_LUX;
  }else{
    reference = HIGH_LUX;
  }
}

/***********************************************
 *  DeadZone
 *    - Trims the response to low errors in order
 *      to avoid actions to quantization noise...
 *  Parameters: error - error value to be trimmed
 *  Returns: double error trimmed
 ***********************************************/
double PID::DeadZone(double error){
  if(error >= ERROR_MAX){
    return error - ERROR_MAX;
  }else if(error <= ERROR_MIN){
    return error + ERROR_MIN; 
  }
  return 0;  
}

/***********************************************
 *  PmwLimiter
 *    - Constrains the PMW values to 0-255 range
 *      to avoid saturation
 *  Parameters: pmw - pmw value to be fed to LED
 *  Returns: int saturation checked pmw value
 ***********************************************/
int PID::PmwLimiter(int pmw){
  if(pmw >= 255){
    return 255;
  }else if(pmw <= 0){
    return 0; 
  }
  return pmw;  
}

/***********************************************
 *  AntiWindup
 *    - Computes the error between input, and
 *      saturation check of same input with a gain
 *      to avoid error accumulation in integral
 *      control component.
 *  Parameters: u - output of control block
 *  Returns: int value to be fed back into integral
 *           control
 ***********************************************/
int PID::AntiWindup(int u){
   return KS*(PmwLimiter(u)-u);
}

/***********************************************
 *  AnalogReadAvg
 *    - Makes n analogReads from specified pin
 *      and computes the average value
 *  Parameters: pin - pin to read values from;
 *              n - number of reads to compute
 *  Returns: int average of the reads made
 ***********************************************/
int PID::AnalogReadAvg(int pin, int n){
  int counter, avg = 0;
  for(counter=0; counter<n; counter++)
    avg += analogRead(pin); 
  return avg/n;
}


/***********************************************
 *  FeedForward
 *    - Implements a feed forward block for
 *      the control system
 *  Returns: double feed forward block response
 *                  to input reference Lux
 ***********************************************/
double PID::FeedForward(){
  return reference*Kf;
}

/***********************************************
 *  ProportionalControl
 *    - Implements a feed fback proportional block 
 *      for the control system
 *  Parameter: error - reference to system output
 *                     comparison
 *  Returns: double proportional control block response
 ***********************************************/
double PID::ProportionalControl(double error){
  return Kp*error);  
}

/***********************************************************
 *  IntegralControl
 *    - Implements a feed fback Integral block 
 *      for the control system
 *  Parameter: integral - previous iteration computed 
 *                        integral value
 *             err - reference to system output comparison
 *             prev_err - previous iteration error
 *  Returns: double Integral control block response
 ***********************************************************/
double PID::IntegralControl(double integral, double err, double prev_err){
  return integral + ((this->K2)*(err+prev_err));
}

/***********************************************************
 *  DerivativeControl
 *    - Implements a feed fback Derivative block 
 *      for the control system
 *  Parameter: y - system output
 *             prev_y - system output on previous iteration
 *  Returns: double Derivative control block response
 ***********************************************************/
double PID::DerivativeControl(double y, double prev_y){
  return K3*(y-prev_y);  
}
