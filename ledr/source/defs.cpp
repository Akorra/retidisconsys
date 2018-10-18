#include "../headers/defs.h"

int to_csv(unsigned long timestamp, double vi, double vo, int lux){
  ofstream csv;
  csv.open("../bin/data.csv");
  csv << timestamp << "," << vi << "," << vo << "," << lux << std::endl;
  


}
