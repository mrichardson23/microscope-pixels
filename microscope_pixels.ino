#include <Adafruit_NeoPixel.h>

#define PIN 6
#define PIXELS 17

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


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  for (int i = 0; i < modes; i++) {
    for (int j = 0; j < PIXELS; j+=2)
    {
      setColorMode(i, j);
      delay(1000);
    }
  }
  
}


void setColorMode(int mode) {
  for (int i = 0; i < PIXELS -1; i++) {
    strip.setPixelColor(i, colorModes[mode][i]);
  }
  strip.show();
}

void setColorMode(int mode, int pixels) {
  clearPixels();
  for (int i = 0; i < pixels -1; i++) {
    strip.setPixelColor(i, colorModes[mode][i]);
  }
  strip.show();
}

void clearPixels() {
  for (int i = 0; i < PIXELS -1; i++) {
    strip.setPixelColor(i,0,0,0);
  }
}

