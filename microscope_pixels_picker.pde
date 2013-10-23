/**
 * Micrope RGB Ringlight Pixel with color Picker 
 * 
 * Demonstrates how to transmit the bytes via serial to the Microscope RGB Ringlight. 
 * Using controlP5: http://www.sojamo.de/libraries/controlP5/
 */

import processing.serial.*;
import controlP5.*;

color theColor = color(100, 100, 100);

ControlP5 cp5;
ColorPicker picker;
Button button;
Range range;

Serial myPort;

void setup() 
{
  size(400, 300);
  noStroke();
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  cp5 = new ControlP5(this);
  picker = cp5.addColorPicker("picker")
    .setPosition(60, 50)
    .setColorValue(theColor)
    .setBarHeight(50)
    ;
  button = cp5.addButton("sendColor")
    .setValue(0)
    .setPosition(50, 220)
    .setSize(275, 35)
    .setCaptionLabel("Send this color")
    ;
  range = cp5.addRange("rangeController")
    .setBroadcast(false) 
    .setPosition(50, 150)
    .setSize(250, 40)
    .setHandleSize(10)
    .setRange(1, 17)
    .setRangeValues(1, 17)
    .setNumberOfTickMarks(16)
    .showTickMarks(true) 
    .snapToTickMarks(true)
    .setCaptionLabel("LEDs")
    // after the initialization we turn broadcast back on again
    .setBroadcast(true)
    .setColorForeground(color(255, 40))
    .setColorBackground(color(255, 40))  
    ;
}

void draw() {
  background(0, 75, 111);
  fill(picker.getColorValue());
  rect(50, 40, 275, 90);
}

void writePixels(color[] pixels) {
  for (int i = 0; i < pixels.length; i++) {
    myPort.write(byte(red(pixels[i])));
    myPort.write(byte(green(pixels[i])));
    myPort.write(byte(blue(pixels[i])));
  }
} 

public void sendColor(int theValue) {
  color[] pixels=new color[17];
  for (int i = 0; i < pixels.length; i++) {
    if ( ((i + 1) >=int(range.getLowValue())) &&  ((i + 1) <= int(range.getHighValue()))) {
      pixels[i] = picker.getColorValue();
    }
    else {
      pixels[i] = color(0, 0, 0);
    }
  }
  writePixels(pixels);
}

