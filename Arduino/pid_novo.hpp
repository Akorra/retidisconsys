#ifndef _PID_HPP_
#define _PID_HPP_

#include "defs.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>

#define KI 10.0
#define KD 0.001
#define KP 1.65
#define KF 2.124
#define KS 0.05
#define TS 0.03

/***********************************************
 *
 ***********************************************/
class PID{
  private:
    double reference;   // Reference LUX value
    double Kf;          // FeedForward Gain
    double Kp;          // Proportional Gain
    double Ki;          // Integral Gain
    double Kd;          // Derivative Gain
    double Ts;          // Sampling Time
    double K2;          // Integral block gain
    double K3;          // Derivative block gain

  public:
    PID();
    /**Setters**/
    void SetKi(double gain);
    void SetKp(double gain);
    void SetKd(double gain);
    void SetKf(double gain);
    void SetRef(double ref);

    /**Getters**/
    double GetKi();
    double GetKp();
    double GetKd();
    double GetKf();
    double GetK2();
    double GetK3();
    double GetRef();

    /**Helper Functions**/
    void LightSwitch();
    int AnalogReadAvg(int pin, int n);

    /**Control Blocks**/
    double DeadZone(double y);
    int PmwLimiter(int pmw);
    int AntiWindup(int u, int u_sat);
    double FeedForward();
    double ProportionalControl(double error);
    double IntegralControl(double integral, double err, double prev_err);
    double DerivativeControl(double y, double prev_y);
};

#endif

