/*
    Works on all boards - not CircuitPlayground see other file.

    OLED using I2C
    KEYBOARD USB to input the HEX code into where their curcor is
    Uses button / conductive fabric to press to copy the code to text file

    NEOs on PIN 10
    Touch INPUT on PIN A9 check your board

*/

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "ADCTouch.h"
#include "Adafruit_NeoPixel.h"
#include "Keyboard.h"
#include <Wire.h>                  //include Wire.h to be able to communicate through I2C on Arduino board
#include "Adafruit_TCS34725.h"     //Colour sensor library

//Create colour sensor object declaration, to see effects of different integration time and gain
//settings, check the datatsheet of the Adafruit TCS34725.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define NEOPIX_PIN    10   // Change to the pin your neopixels are on
#define NUM_PIXELS    25   // change to the number of NeoPixels you are using
Adafruit_NeoPixel strip(NUM_PIXELS, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

float r, g, b;
int ref0;
int touchPin = A9;
int threshold = 10;
int val0high = 35;
int val0low = 0;

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ************************ SETUP ***************************************************//

void setup() {
  Serial.begin(9600);
 
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.setPixelColor(0, 255,   0,   0);
  strip.setPixelColor(1, 128, 128,   0);
  strip.setPixelColor(2,   0, 255,   0);
  strip.setPixelColor(3,   0, 128, 128);
  strip.setPixelColor(4,   0,   0, 255);
  strip.show();
  delay(3000);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed to load"));
    //while (true);
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  ref0 = ADCTouch.read(touchPin, 500);

  //Start-up colour sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No Color Sensor found ... check your connections");
    //while (1); // halt!
  }
  Keyboard.begin();
}

// ************************ LOOP ***************************************************//

void loop() {

  uint16_t clear, red, green, blue;

  //Collect raw data from integrated circuit using interrupts
  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;

  r = red;
  r /= sum;
  g = green;
  g /= sum;
  b = blue;
  b /= sum;
  r *= 256; g *= 256; b *= 256;
  
  int value0 = ADCTouch.read(touchPin);
  value0 -= ref0;
  Serial.println(value0);
  if (value0 > threshold) {
    Serial.println("Touch detected");
    Keyboard.print((int)r, HEX);
    delay(300);
    Keyboard.print((int)g, HEX);
    delay(300);
    Keyboard.print((int)b, HEX);
    Serial.println("button");
    Keyboard.println();
    delay(300);
  }

  Serial.print("HEX: \t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.print("\t \t RGB: \t");
  Serial.print((int)r );
  Serial.print(" ");
  Serial.print((int)g);
  Serial.print(" ");
  Serial.println((int)b );
  Serial.println();

  colorWipe(strip.Color(r, g, b), 50);

  runOLED();

}


// ******************************** FUNCTIONS ******************************

void runOLED(){
  
  oled.clearDisplay();          // clear display
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(1, 1);        // position to display
  oled.println("Send HEX to your computer. Touch.");

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(2, 30);        // position to display
  oled.println("HEX:");
  oled.setCursor(50, 30);        // position to display
  oled.println((int)r, HEX);
  oled.setCursor(74, 30);        // position to display
  oled.println((int)g, HEX);
  oled.setCursor(98, 30);        // position to display
  oled.println((int)b, HEX);     // text to display
  oled.display();                // show on OLED

  delay(2000);
}


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  }
  delay(wait);                           //  Pause for a moment
}
