const double m = -0.61092;
const double b = 4.69897;

unsigned long starTime = 0;
int sensorValue = 0;
int stoploop = 1;
double sensorVoltage = 0;
double sensorLux = 0;
double ledVoltage = 0;

double volt2lux(double volt){
  return pow(((5/volt)-1)*10000/pow(10,b),1/m);  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  Serial.begin(230400);
  Serial.println("\nTimestamp,LED,Vi,Vo,LUX");
}

void loop() {
  if(stoploop){
    for(int i=0; i<=250; i+=50){
      analogWrite(10, i);
      starTime = micros();
      while(micros()-starTime < 5000000){
        ledVoltage = (double)i*0.015;
        sensorValue = analogRead(0);
        sensorVoltage = (double)sensorValue*5.0/1023;
        sensorLux = volt2lux(sensorVoltage);
      
        Serial.print(micros());
        Serial.print(",");
        Serial.print(i);
        Serial.print(",");
        Serial.print((double)ledVoltage, 5);
        Serial.print(",");
        Serial.print((double)sensorVoltage, 5);
        Serial.print(",");
        Serial.print((double)sensorLux, 5);
        Serial.println();
        delay(5); /*5 ms sampling rate*/
      }  
    }
    stoploop = 0;
    Serial.println("FINISHED STEP RESPONSES");
  }
}
