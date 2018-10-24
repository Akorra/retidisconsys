#ifndef _PID_HPP_
#define _PID_HPP_

#include "defs.hpp"

class PID{
  private:
    double K0;
    int reference;
    int response;
    unsigned long wait;
    unsigned long present;
    unsigned long previous;
    
  public:
    PID();
    PID(double K, int ref, unsigned long wait);
    bool FeedForward(double y, const int LedPin);
    void SetReference(int ref);
    void SetTimeConst(unsigned long w8);
    void SetGainConst(double K);
    void GetReference();
};

#endif
