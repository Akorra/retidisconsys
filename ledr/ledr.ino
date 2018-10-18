const int LDR = 0;
const int LED = 10;

int raw = 0;
int v1 = 0;
int led = 0;
char out[128]; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  raw = analogRead(0);
  v1 = raw*5.0/1.0230;
  sprintf(out, "%d-%ld-%d", v1, micros(), raw);
  Serial.println(out);
  delay(1000);
}
