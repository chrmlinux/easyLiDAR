#include <FastLED.h>
#define MAT_LED (27)
#define MAT_WIDTH (5)
#define MAT_HEIGHT (5)
#define NUM_LEDS (MAT_WIDTH * MAT_WIDTH)
CRGB leds[NUM_LEDS];

void setupLeds(void) {
  FastLED.addLeds<NEOPIXEL, MAT_LED>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  memset(leds, 0x0, sizeof(leds));
}
