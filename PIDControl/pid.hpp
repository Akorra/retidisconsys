#ifndef _PID_HPP_
#define _PID_HPP_

#include "defs.hpp"

#define KI 10.0
#define KD 0.001
#define KP 1.65
#define KF 2.124
#define KS 0.05
#define TS 0.03

class PID{
  private:
    double reference;
    double Ki;
    double Kp;
    double K2; 
    double K3; 

  public:
    PID();
    void SetKi(double i);
    void SetKp(double j);
    void UpdateK2();
    void SetRef(double ref);
    double GetKi();
    double GetKp();
    double GetK2();
    double GetRef();
    void LightSwitch();
    double DeadZone(double y);
    int PmwLimiter(int pmw);
    int AntiWindup(int u, int u_sat);
    int AnalogReadAvg(int pin, int n);
    double FeedForward();
    double ProportionalControl(double error);
    double IntegralControl(double integral, double err, double prev_err);
    double DerivativeControl(double y, double prev_y);
};

#endif
