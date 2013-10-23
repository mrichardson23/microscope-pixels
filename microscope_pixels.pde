/**
 * Micrope RGB Ringlight Pixel Sender 
 * 
 * Demonstrates how to transmit the bytes via serial to the Microscope RGB Ringlight. 
 * TODO: function to transmit array of colors
 * TODO: make GUI for selecting values to send.
 *
 */

import processing.serial.*;

color[] pixels=new color[18];

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
  color[] testPattern=new color[18];
  for (int i = 0; i < testPattern.length; i++) {
    if (i%3 == 0) {
      testPattern[i] = color(255, 0, 0);
    }
    if (i%3 == 1) {
      testPattern[i] = color(0, 255, 0);
    }

    if (i%3 == 2) {
      testPattern[i] = color(0, 0, 255);
    }
  }

  for (int i = 0; i < testPattern.length; i++) {
    myPort.write(byte(red(testPattern[i])));
    myPort.write(byte(green(testPattern[i])));
    myPort.write(byte(blue(testPattern[i])));
  }
}

