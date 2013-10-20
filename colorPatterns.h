// This creates a two-dimensional array. Each parent element
// must contain 17 uint32_t child elements for each pixel.
// each pixel's color is defined by:
// strip.Color(R, G, B)

// Each mode MUST have 17 colors.

// To access a pixel's color, you'd use modes[0][0] for the first pixel
// in the first mode. modes[0][1] would be the second pixel in the first
// mode. modes[1][0] would be the first pixel in the second mode.

uint32_t colorModes[][17] =
{ 
  {  // color mode 1, all white:
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255),
    strip.Color(255, 255, 255)
    },
  {  // color mode 2, all red:
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 0)
    },
  {  // color mode 3, all green:
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 0)
    },

  {  // color mode 4, all blue:
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255),
    strip.Color(0, 0, 255)
    },
  {  // color mode 5, all yellow:
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 0)
    },
  {  // color mode 6, all magenta:
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255),
    strip.Color(255, 0, 255)
    },
  {  // color mode 7, all cyan:
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
    strip.Color(0, 255, 255),
  }
};

// The lines below determine how many modes are listed above
// This way

int sizeOfEachMode = sizeof(uint32_t) * 17;
int modes = sizeof(colorModes) / sizeOfEachMode;

