#include <math.h>

namespace Defs {
  const double M = -0.6316;
  const double B = 4.74;
  const double VDD = 5.0;
  const double R1 = 10000.0;
  const double MAX_LUX = 75;
  const double HIGH_LUX = 50;
  const double LOW_LUX = 20;
  const double ERROR_MAX = 1;

  double volt2lux(double volt);
  double raw2volt(int raw);
}
