
// Read the temperature using a Velleman 320 thermistor, and write the result to the serial port.
// Adapted from: https://stackoverflow.com/questions/44747996/arduino-temperature-sensor-counting-back
// Pin order is: Signal (left), 5V power (middle), Ground (right)

#include <math.h>

const int thermistorPin = 0;

double readThermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0/(1024.0/RawADC - 1)); // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741*Temp*Temp))*Temp);
  Temp = 1.8*(Temp - 273.15) + 32.0; // Convert Kelvin to Fahrenheit
  return Temp;
}

void setup() {
 Serial.begin(9600);
}

void loop() {
 Serial.print(readThermistor(analogRead(thermistorPin)));
 Serial.println("° F");
 delay(250);
}
