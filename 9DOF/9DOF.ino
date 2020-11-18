
#include <U8glib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>

// OLED display parameters.
#define numLines 4 // 4 lines is recommended, but 5 also works.

const int clkPin = 8;
const int mosiPin = 9;
const int csPin = 6;
const int dcPin = 7;
const boolean flipped = false;
U8GLIB_SH1106_128X64 u8g(clkPin, mosiPin, csPin, dcPin);
int deltaRow = 16, firstRow = 14;
String text[] = { "", "", "", "", "" };


/* Assign a unique IDs to these sensors at the same time. */
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);


void setup(void) {
  
  Serial.begin(9600);
  while (!Serial) { delay(1); }

  if(!accelmag.begin(ACCEL_RANGE_4G)) {
    Serial.println("No Accel/Mag");
    while(1);
  }

  if(!gyro.begin()) {
    Serial.println("No gyro");
    while(1);
  }

  displaySensorDetails();

  // Set up OLED
  u8g.setFont(u8g_font_unifont); // 16 x 16
  if (numLines == 5) { deltaRow = 12; }  
  if (flipped) {
    u8g.setRot180(); // flip screen
    firstRow = 12; 
  }    
}

void loop(void) {

  sensors_event_t aevent, mevent, gyroEvent;
  accelmag.getEvent(&aevent, &mevent);
  gyro.getEvent(&gyroEvent);
  
//  text[0] = "Accelerometer";
//  text[1] = "X: " + String(aevent.acceleration.x, 4) + " m/s2";
//  text[2] = "Y: " + String(aevent.acceleration.y, 4) + " m/s2";
//  text[3] = "Z: " + String(aevent.acceleration.z, 4) + " m/s2";
  
  text[0] = "Magnetometer";
  text[1] = "X: " + String(mevent.magnetic.x, 1) + " uT";
  text[2] = "Y: " + String(mevent.magnetic.y, 1) + " uT";
  text[3] = "Z: " + String(mevent.magnetic.z, 1) + " uT";
  
//  text[0] = "Gyro";
//  text[1] = "X: " + String(gyroEvent.gyro.x, DEC) + " rad/s";
//  text[2] = "Y: " + String(gyroEvent.gyro.y, DEC) + " rad/s";
//  text[3] = "Z: " + String(gyroEvent.gyro.z, DEC) + " rad/s";

  u8g.firstPage();
  do {
    draw();
  } while(u8g.nextPage());
    
  delay(50);
}

void displaySensorDetails(void) {
  sensor_t accel, mag, gyroSensor;
  accelmag.getSensor(&accel, &mag);
  gyro.getSensor(&gyroSensor);
  Serial.println("------------------------------------");
  Serial.println("ACCELEROMETER");
  Serial.println("------------------------------------");
  Serial.print("Sensor: "); Serial.println(accel.name);
  Serial.print("Driver Ver: "); Serial.println(accel.version);
  Serial.print("Unique ID: 0x"); Serial.println(accel.sensor_id, HEX);
  Serial.print("Min Delay: "); Serial.print(accel.min_delay); Serial.println(" s");
  Serial.print("Min Value: "); Serial.print(accel.min_value, 4); Serial.println(" m/s^2");
  Serial.print("Max Value: "); Serial.print(accel.max_value, 4); Serial.println(" m/s^2");
  Serial.print("Resolution: "); Serial.print(accel.resolution, 8); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("MAGNETOMETER");
  Serial.println("------------------------------------");
  Serial.print("Sensor: "); Serial.println(mag.name);
  Serial.print("Driver Ver: "); Serial.println(mag.version);
  Serial.print("Unique ID: 0x"); Serial.println(mag.sensor_id, HEX);
  Serial.print("Min Delay: "); Serial.print(mag.min_delay); Serial.println(" s");
  Serial.print("Min Value: "); Serial.print(mag.min_value); Serial.println(" uT");
  Serial.print("Max Value: "); Serial.print(mag.max_value); Serial.println(" uT");
  Serial.print("Resolution: "); Serial.print(mag.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("GYRO");
  Serial.println("------------------------------------");
  Serial.print ("Sensor: "); Serial.println(gyroSensor.name);
  Serial.print("Driver Ver: "); Serial.println(gyroSensor.version);
  Serial.print("Unique ID: 0x"); Serial.println(gyroSensor.sensor_id, HEX);
  Serial.print("Min Value: "); Serial.print(gyroSensor.min_value); Serial.println(" rad/s");
  Serial.print("Max Value: "); Serial.print(gyroSensor.max_value); Serial.println(" rad/s");
  Serial.print("Resolution: "); Serial.print(gyroSensor.resolution); Serial.println(" rad/s");
  Serial.println("------------------------------------");
}

void draw(void) {
  char charBuffer[16];
  for (int i = 0; i < numLines; i++) {
    text[i].toCharArray(charBuffer, 16);
    u8g.drawStr(0, firstRow + i*deltaRow, charBuffer);
  }
}
