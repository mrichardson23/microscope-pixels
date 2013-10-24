/**
 * Micrope RGB Ringlight Pixel with color Picker 
 * 
 * Demonstrates how to transmit the bytes via serial to the Microscope RGB Ringlight. 
 * Using controlP5: http://www.sojamo.de/libraries/controlP5/
 */

import processing.serial.*;
import controlP5.*;

static final int interval = 100;
int prevMillis = 1000;

// Global array of color pixels:
color[] pixels=new color[17];

// UI Objects:
ControlP5 cp5;
ColorPicker picker1;
ColorPicker picker2;
Button button;
Button offButton1;
Button offButton2;
Range range;
Toggle transmit;

Serial myPort;

void setup() 
{
  size(680, 500);
  noStroke();
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 115200);
  
  // UI Element Setup:
  cp5 = new ControlP5(this);
  picker1 = cp5.addColorPicker("picker1")
    .setPosition(50, 50)
    .setColorValue(color (0, 0, 255))
    .setBarHeight(50)
    .setLabel("Color A")
    ;
  picker2 = cp5.addColorPicker("picker2")
    .setPosition(350, 50)
    .setColorValue(color (255, 0, 0))
    .setBarHeight(50)
    .setLabel("Color B")
    ;

  range = cp5.addRange("rangeController")
    .setBroadcast(false) 
    .setPosition(50, 150)
    .setSize(560, 40)
    .setHandleSize(10)
    .setRange(1, 17)
    .setRangeValues(1, 17)
    .setNumberOfTickMarks(16)
    .showTickMarks(true) 
    .snapToTickMarks(false)
    .setLabelVisible(false) 
    .setHighValue(9.5) 
    .setLowValue(9) 
    // after the initialization we turn broadcast back on again
    .setBroadcast(true)
    .setColorForeground(color(255, 40))
    .setColorBackground(color(255, 40))
    ;

  button = cp5.addButton("sendColor")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(50, 400)
    .setSize(560, 35)
    .setCaptionLabel("Send this Pattern")
    .setBroadcast(true)
    ;
    
  offButton1 = cp5.addButton("offButton1")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(50, 120)
    .setSize(35, 20)
    .setCaptionLabel("Off")
    .setBroadcast(true)
    ;

  offButton2 = cp5.addButton("offButton2")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(350, 120)
    .setSize(35, 20)
    .setCaptionLabel("Off")
    .setBroadcast(true)
    ;
    
    
 transmit = cp5.addToggle("transmit")
     .setPosition(50,350)
     .setSize(50,20)
     .setValue(false)
     .setCaptionLabel("ON TRANSMIT OFF") 
     .setMode(ControlP5.SWITCH)
     ;
     
  setPixels();
  

}

void draw() {
  background(0, 75, 111);
  
  // Create the simulation graphic:
  pushMatrix();
    translate(width/2, 300);
    for (int i = 0; i < pixels.length; i++) {
      fill(pixels[i]);
      ellipse(0, 60, 15, 15);
      rotate(radians(360.0/17.0));
    }
  popMatrix();
  
  if (millis() > prevMillis + interval) {
    if (transmit.getValue() != 0.0)
      writePixels(pixels);
    prevMillis = millis();
  }
  
}

void writePixels(color[] pixels) {
  // Go through each item in the array,
  // send values for R,G,B as bytes
  color[] reversePixels = reverse(pixels);
  for (int i = 0; i < reversePixels.length; i++) {
    myPort.write(byte(red(reversePixels[i])));
    myPort.write(byte(green(reversePixels[i])));
    myPort.write(byte(blue(reversePixels[i])));
  }
} 

public void controlEvent(ControlEvent theControlEvent) {
  // When any UI element is updated, refresh the pixel array
  if (theControlEvent.isFrom("rangeController") || theControlEvent.isFrom("picker1") ||
    theControlEvent.isFrom("picker2") || theControlEvent.isFrom("offButton1") ||
    theControlEvent.isFrom("offButton2")) {
    setPixels();
  }
}

public void sendColor(int theValue) {
  writePixels(pixels);
}

public void offButton1(int theValue) {
  picker1.setColorValue(color(0, 0, 0));
}
public void offButton2(int theValue) {
  picker2.setColorValue(color(0, 0, 0));
}

void setPixels() {
  // based on color pickers and range selector, set the values in the 
  // pixels array. For each pixel, evaluate where it is in relation
  // to the range selector and act accordingly
  float gradientRange = range.getHighValue() - range.getLowValue();
  for (int i = 0; i < pixels.length ; i++) {
    if (i >= int(range.getHighValue())) {
      pixels[i] = picker2.getColorValue();
    }
    else if (i <= int(range.getLowValue())) {
      pixels[i] = picker1.getColorValue();
    }
    else if ( ((i + 1) >=int(range.getLowValue())) &&  ((i + 1) <= int(range.getHighValue()))) {
      // if you're between the range sliders, calculate the appropriate gradient:
      float lerpPos = float(i) - range.getLowValue();
      pixels[i] = lerpColor(picker1.getColorValue(), picker2.getColorValue(), lerpPos / gradientRange);
    }
    else {
      pixels[i] = color(0, 0, 0);
    }
  }
}

