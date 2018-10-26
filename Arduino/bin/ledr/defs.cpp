#include "defs.hpp"

namespace Defs {
  double volt2lux(double volt){
    return pow(10.0, (log10(R1*((VDD/volt)-1))-B)/M);
  }
  double raw2volt(int raw){
    return (raw*VDD)/1023.0;
  }
}
