#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 4
#define NUM 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

uint32_t prevTime;
uint32_t color = 0xff0000;
uint32_t red = 0xff0000;
uint32_t yellow = 0xffff00;
uint32_t green = 0x00ff00;
uint32_t blue = 0x0000ff;
uint32_t violet = 0xff00ff;

uint32_t colors[] = {red,yellow,green,blue,violet};

uint8_t  mode   = 0; // Current animation effect
uint8_t  offset = 0; // Position of spinner
uint8_t  index  = 0;

void setup() {
  strip.begin();
  strip.setBrightness(60); // 1/3 brightness
  prevTime = millis();
}

void loop() {
  uint32_t t;
  uint32_t threshold;
  
  switch(mode) {
    case 0:
      threshold = 2000; // 2 seconds...
      randomColorSpark();
      break;
    case 1:
      threshold = 1500; // 1.5 seconds...
      clockwiseSpinner();
      break;
    case 2:
      threshold = 1500; // 1.5 seconds...
      counterClockwiseSpinner();
      break;
  }
 
  t = millis();
  if((t - prevTime) > threshold) { // Every ? seconds...
    mode++;                        // Next mode
    if(mode > 2) {                 // End of modes?
      mode = 0;                    // Start modes over
      index++;
      if(index > 4) index = 0;
      color = colors[index];
    }
    resetPixels();
    prevTime = t;
  }
}

void clockwiseSpinner() {
  for(uint8_t i=0; i<NUM; i++) {
    uint32_t c = 0;
    if(((offset + i) & 7) < 2) c = color; // 2 pixels on...
      strip.setPixelColor(i, c);
  }
  strip.show();
  offset++;
  delay(50);
}

void counterClockwiseSpinner() {
  for(uint8_t i=NUM; i>0; i--) {
    uint32_t c = 0;
    if(((offset + (i-1)) & 7) < 2) c = color; // 2 pixels on...
      strip.setPixelColor(i-1, c);
  }
  strip.show();
  offset--;
  delay(50);
}

void randomColorSpark() {
  uint8_t n = random(5);
  uint8_t i = random(NUM);
  strip.setPixelColor(i, colors[n]);
  strip.show();
  delay(10);
  strip.setPixelColor(i, 0);
}

void resetPixels() {
  for(uint8_t i=0; i<NUM; i++) strip.setPixelColor(i, 0);
}
