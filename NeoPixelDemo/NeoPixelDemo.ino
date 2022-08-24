
// My NeoPixel demo, adapted from the built-in "strandtest" demo in the 
// Adafruit NeoPixel library.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN 5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60
#define APPARENT_LED_COUNT 20
#define ONE_SECOND_INTERVAL 50   
//   = 1000 ms / 20 LEDs

// Declare the NeoPixel strip object.
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
// NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
// NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // turn off all pixels initially
  strip.setBrightness(50); // set 20% brightness (max = 255)
}

void loop() {
  
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t green = strip.Color(0, 255, 0);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t orange = strip.Color(255, 76, 13);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t light_white = strip.Color(127, 127, 127);
  uint32_t light_red = strip.Color(127, 0, 0);
  uint32_t light_blue = strip.Color(0, 0, 127);
  
  // Fill along the length of the strip in various colors...
  for (int i = 0; i < 5; i++) {
    wipeColor(red, 0.33*ONE_SECOND_INTERVAL, true);
    wipeColor(green, 0.33*ONE_SECOND_INTERVAL, true);
    wipeColor(blue, 0.33*ONE_SECOND_INTERVAL, true);
  }

  // Fill up, then reverse.
  for (int i = 0; i < 5; i++) {
    wipeColor(orange, 0.5*ONE_SECOND_INTERVAL, true);
    wipeColor(blue, 0.5*ONE_SECOND_INTERVAL, false);
  }

  // Fill up brightness, then reverse.
  for (int i = 0; i < 5; i++) {
    wipeBrightness(green, 50, 0.5*1000/50, true);
    wipeBrightness(green, 50, 0.5*1000/50, false);
  }
  strip.setBrightness(50);

  // Run a single train of white light around the strip.
  for (int i = 0; i < 5; i++) {
    train(light_white, 50);
  }

  // Do a theater marquee effect in a single color.
  for (int i = 0; i < 25; i++) {
    theaterChase(light_white, 50);
  } 

  // Do a theater marquee effect in a sequence of rainbow colors.
  theaterChaseRainbow(50);

  // Flowing rainbow cycle along the whole strip.
  wipeRainbow(10);
}

/*
 * Writes a color to each pixel from the beginning to the end of the strip.
 * 
 * color - a single 'packed' 32-bit value (which you can get by calling 
 * strip.Color(red, green, blue) 
 * 
 * delayPeriod_ms - delay time in milliseconds between pixel updates
 * 
 * wipeUp - true to change pixels in sequence from the start to the end of 
 * the strip, or false to change them in the reverse direction
 */
void wipeColor(uint32_t color, int delayPeriod_ms, boolean wipeUp) {

  if (wipeUp) {
    for(int i = 0; i < APPARENT_LED_COUNT; i++) {
      strip.setPixelColor(i, color); // set pixel i color in RAM
      strip.show();
      delay(delayPeriod_ms);
    }
  } else {
    for(int i = APPARENT_LED_COUNT - 1; i >= 0; i--) {
      strip.setPixelColor(i, color); // set pixel i color in RAM
      strip.show();
      delay(delayPeriod_ms);
    }
  }    
}


/*
 * Writes a color to each pixel from the beginning to the end of the strip.
 * 
 * color - a single 'packed' 32-bit value (which you can get by calling 
 * strip.Color(red, green, blue)
 * 
 * maxBrightness - 0 to 255, representing maximum brightness value used
 * 
 * delayPeriod_ms - delay time in milliseconds between pixel updates
 * 
 * wipeUp - true to change pixels in sequence from the start to the end of 
 * the strip, or false to change them in the reverse direction
 */
void wipeBrightness(uint32_t color, int maxBrightness, int delayPeriod_ms, boolean wipeUp) {
  

  if (wipeUp) {
    for(int b = 0; b < maxBrightness; b++) {
      strip.fill(color, 0, APPARENT_LED_COUNT - 1);
      strip.setBrightness(b);
      strip.show();
      delay(delayPeriod_ms);
    }
  } else {
    for(int b = maxBrightness; b >= 0; b--) {
      strip.fill(color, 0, APPARENT_LED_COUNT - 1);
      strip.setBrightness(b);
      strip.show();
      delay(delayPeriod_ms);
    }
  }
}


/* 
 * Displays a train of lights traversing the strip.
 * 
 * Pass in a color as a single 'packed' 32-bit value (which you can get 
 * by calling strip.Color(red, green, blue) as shown in the loop() function 
 * above), and a delay time in milliseconds.
 */
void train(uint32_t color, int delayPeriod_ms) {
  const int kTrainSize = 3;
  for(int startPosition = 0; startPosition < APPARENT_LED_COUNT; startPosition++) {
    strip.clear();
    for(int p = startPosition; p < startPosition + kTrainSize; p++) { 
      strip.setPixelColor(p % APPARENT_LED_COUNT, color);
    }
    strip.show();
    delay(delayPeriod_ms);
  }
}

/* 
 * Displays a lights animation in the style of a theater-marquee. 
 * 
 * Pass in a color as a single 'packed' 32-bit value (which you can get 
 * by calling strip.Color(red, green, blue) as shown in the loop() function 
 * above), and a delay time in milliseconds.
 */
void theaterChase(uint32_t color, int delayPeriod_ms) {
  const int kBandSize = 5;
  for(int b = 0; b < kBandSize; b++) {
    strip.clear();
    for(int c = b; c < strip.numPixels(); c += kBandSize) { 
      strip.setPixelColor(c, color); 
    }
    strip.show();
    delay(delayPeriod_ms);
  }
}


// Displays rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {

  // First pixel starts at red (hue 0)
  int firstPixelHue = 0;
  
  // Repeat 30 times...
  for(int a = 0; a < 30; a++) {

    // 'b' counts from 0 to 2...
    for(int b = 0; b < 3; b++) { 
      
      strip.clear();
      
      // 'c' counts up from 'b' to end of strip in increments of 3...      
      for(int c = b; c < strip.numPixels(); c += 3) {
        
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      
      strip.show();
      delay(wait);

      // One cycle of color wheel over 90 frames
      firstPixelHue += 65536 / 90; 
    }
  }
}


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void wipeRainbow(int delayPeriod_ms) {
  
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 512 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 512) {

    // For each pixel in strip...
    for(int i = 0; i < strip.numPixels(); i++) {
      
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    
    strip.show();
    delay(delayPeriod_ms);
  }
}
