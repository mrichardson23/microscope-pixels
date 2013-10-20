#include <Adafruit_NeoPixel.h>

#define PIN 6
#define PIXELS 17
#define STEPS_PER_MODE 4

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
// tab.
#include "colorPatterns.h"

int mode = 0;
int step = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    // if we receive a serial byte...
    if (step < PIXELS) {
      // if we have more steps to go before filling the strip,
      // add one "step" to the current mode.
      step += PIXELS / STEPS_PER_MODE;
    }
    else {
      // if the strip is full, we go back to step 0
      step = 0;
      if (mode < modes-1) {
        // if we have more modes, we go to the next.
        mode++;
      }
      else {
        // if we're at the last mode, go to the first.
        mode = 0;
      }
    }
    // set the mode and step:
    setColorMode(mode, step);

    Serial.print(mode);
    Serial.print(",");
    Serial.println(step);
    
    Serial.read(); // remove the byte from the buffer
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
  for (int i = 0; i < pixels -1; i++) {
    strip.setPixelColor(i, colorModes[mode][i]);
  }
  strip.show();
}

void clearPixels() {
  for (int i = 0; i < PIXELS; i++) {
    strip.setPixelColor(i,0,0,0);
  }
}


