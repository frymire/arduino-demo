
// https://stackoverflow.com/questions/44747996/arduino-temperature-sensor-counting-back

#include <math.h>

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0/(1024.0/RawADC - 1)); // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741*Temp*Temp))* Temp );
  Temp = 1.8*(Temp - 273.15) + 32.0;            // Convert Kelvin to Fahrenheit
  return Temp;
}

void setup() {
 Serial.begin(9600);
}

void loop() {
// Serial.println(int(Thermistor(analogRead(A0))));
 Serial.print(Thermistor(analogRead(A0)));
 Serial.println("° F");
 delay(250);
}
