
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>

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
}

void loop(void) {
  
  sensors_event_t aevent, mevent, gyroEvent;
  accelmag.getEvent(&aevent, &mevent);
  gyro.getEvent(&gyroEvent);
  
  // Display the accelerometer results.
  Serial.print("Acceleration (m/s^2) ");
  Serial.print("X: "); Serial.print(aevent.acceleration.x, 4); Serial.print("  ");
  Serial.print("Y: "); Serial.print(aevent.acceleration.y, 4); Serial.print("  ");
  Serial.print("Z: "); Serial.print(aevent.acceleration.z, 4); Serial.print("  ");
  
  // Display the magnetometer results.
  Serial.print("Magnetometer (uT) ");
  Serial.print("X: "); Serial.print(mevent.magnetic.x, 1); Serial.print("  ");
  Serial.print("Y: "); Serial.print(mevent.magnetic.y, 1); Serial.print("  ");
  Serial.print("Z: "); Serial.print(mevent.magnetic.z, 1); Serial.print("  ");

  /* Display the results (speed is measured in rad/s) */
  Serial.print("Gyro (rad/s) ");
  Serial.print("X: "); Serial.print(gyroEvent.gyro.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(gyroEvent.gyro.y); Serial.print(" ");
  Serial.print("Z: "); Serial.print(gyroEvent.gyro.z); Serial.print(" ");

  Serial.println("");  
  delay(500);
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
  Serial.println("");
  delay(5000);  
}
