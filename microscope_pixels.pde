/**
 * Micrope RGB Ringlight Pixel Sender 
 * 
 * Demonstrates how to transmit the bytes via serial to the Microscope RGB Ringlight. 
 * TODO: function to transmit array of colors
 * TODO: make GUI for selecting values to send.
 *
 */


import processing.serial.*;

Serial myPort;

void setup() 
{
  size(200, 200);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(255);
}

void mouseReleased() {
  sendTestPattern();
}


void sendTestPattern() {
  // Alternates RGB Pixels
  for (int i = 0; i < 51; i++) {
    if (i%3 == 0) {
      myPort.write(75);
      myPort.write(1);
      myPort.write(1);
    }
    if (i%3 == 1) {
      myPort.write(1);
      myPort.write(75);
      myPort.write(1);
    }

    if (i%3 == 2) {
      myPort.write(1);
      myPort.write(1);
      myPort.write(75);
    }
  }
}
