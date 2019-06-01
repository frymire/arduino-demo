
import processing.serial.*;

// Create a serial port instance.
Serial myPort;

// Store variables for the element of the sketch: the Arduino logo and a background color.
int bgcolor = 0;

void setup() {
  
  // Set up a sketch with the color mode to Hue/Saturation/Brightness.
  size(200, 200);
  colorMode(HSB, 255);

  // Specify the port to listen on.
  //println("Available serial ports:");
  //println(Serial.list());
  myPort = new Serial(this, "COM5", 9600);

}

void draw() {

  // Read and print any new information in the serial port.
  // Without the clear() call, the data stream was very choppy.
  if (myPort.available() > 0) {
    bgcolor = myPort.read();
    myPort.clear();
    println(bgcolor);
  }

  // Draw the background using the hue obtained on the serial port.
  background(bgcolor, 255, 255);
  
}