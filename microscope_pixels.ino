#include <Adafruit_NeoPixel.h>

#define PIN 6
#define PIXELS 17
#define PIXELS_PER_STEP 1

#define NEXT_BUTTON_PIN 7
#define PREV_BUTTON_PIN 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// The following #include must be included AFTER the Adafruit_NeoPixel object is
// instantiated since it uses one of its methods to store RGB values for each
// pixzel as uint32_t. To edit the color patterns, click the colorPatterns.h
// tab. This creates the colorModes[][] array. See the file for more info.
#include "colorPatterns.h"

// The lines below determine how many modes are in the colorModes[][] array.
const int sizeOfEachMode = sizeof(uint32_t) * 17;
const int modes = sizeof(colorModes) / sizeOfEachMode;

// totalSteps factors in each mode AND the number of pixels turned on.
// Having this value is helpful for "rolling over" after reaching
// the last possible mode:
const int totalSteps = modes * PIXELS;

// currentStep holds the current value within totalSteps. This is
// incremented or decremented on button pushes.
int currentStep = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PREV_BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(NEXT_BUTTON_PIN) == LOW) { // if the next button is pushed
    if (currentStep < totalSteps - 1) {
      currentStep += PIXELS_PER_STEP; // Increment the step if there's a next step.
    }
    else {
      currentStep = 0; // if we're at the last step, go to the first step (rollover).
    }
    // figure out what mode we're in and how many pixels to light
    // within that mode:
    setColorMode(currentStep/PIXELS, currentStep%PIXELS);
  }

  if (digitalRead(PREV_BUTTON_PIN) == LOW) { // if the previous button is pushed
    if (currentStep > 0) {
      currentStep -= PIXELS_PER_STEP;  // decrement the step if there's a previous step
    }
    else {
      currentStep = totalSteps - 1; // if we're at the first step, go to the last step (rollover)
    }
    // figure out what mode we're in and how many pixels to light
    // within that mode:
    setColorMode(currentStep/PIXELS, currentStep%PIXELS);
  }
  delay(100); // poor-man's debounce

  // The following is how serial data is used to set the pixels.
  if (Serial.available() > 50) { // do we have enough bytes to set the pixels?
    int i = 0; // count of which pixel we're on
    do {
      int r = Serial.read(); 
      int g = Serial.read();
      int b = Serial.read();
      // get three bytes, write thosee as RGB to the pixel
      strip.setPixelColor(i,r,g,b);
      // increment the pixel
      i++;
    } 
    while (Serial.available());
    strip.show();
    //delay(10);
    // not sure why, but the flush below makes it work.
    // extra bytes aren't being handled, I guess.
    while (Serial.available())
      Serial.read(); 
  }
}

void setColorMode(int mode) {
  // This function reads all the pixels in the
  // mode and sets the pixels accordingly.
  for (int i = 0; i < PIXELS -1; i++) {
    strip.setPixelColor(i, colorModes[mode][i]);
  }
  strip.show();
}

void setColorMode(int mode, int pixels) {
  // This function only sets the first specified
  // number of pixels. The remainder will be dark.
  clearPixels();
  for (int i = 0; i <= pixels; i++) {
    strip.setPixelColor(i, colorModes[mode][i]);
  }
  strip.show();
}

void clearPixels() {
  for (int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i,0,0,0);
  }
}





