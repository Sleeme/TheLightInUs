#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
//Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
}

int frame = 0;

void loop() {
  // animate over all the pixels, and set the brightness from the sweep table
  float brightness = 1.0f / 60.0f * 10;
    for (uint8_t x = 0; x < 15; x++)
      for (uint8_t y = 0; y < 7; y++)
        ledmatrix.drawPixel(x, y, (int) (sweep[(x+y+frame)%24] * brightness));
  delay(20);
  frame++;
}
