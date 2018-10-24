#include <math.h>
#define M -0.6316
#define B 4.74
#define VDD 5.0
#define R1 10000.0
#define MAX_LUX 75
#define HIGH_LUX 50
#define LOW_LUX 20
#define ERROR_MAX 1

namespace Defs {
  double volt2lux(double volt);
  double raw2volt(int raw);
}
