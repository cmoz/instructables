/*
* @cmoz
* This example works with the OUIS instructable
* It is for touch inputs
* you can use any touch inputs, but the example is with conductive fabric
* fabrics from tinkertailor.tech
* using a Circuit Playground board with touch and it's own library
*/

#include <Adafruit_CircuitPlayground.h>

uint8_t pixeln = 0;
int capsense[10];

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  capsense[0] = CircuitPlayground.readCap(3); // this sets each touch input and assigns a pin
  capsense[1] = CircuitPlayground.readCap(2);
  capsense[2] = CircuitPlayground.readCap(0);
  capsense[3] = CircuitPlayground.readCap(1);
  capsense[4] = CircuitPlayground.readCap(12);
  capsense[5] = CircuitPlayground.readCap(6);
  capsense[6] = CircuitPlayground.readCap(9);
  capsense[7] = CircuitPlayground.readCap(10); // currently the tutorial shows 7 touch inputs, you would add another touch area to add this pin

  int frequency = 0;

  if  (capsense[0] > 100) {
    frequency = 523; // this is the sound tone it will play
    CircuitPlayground.setPixelColor(0, 75, 0, 130); //sets a colour for the onboard neopixel
  } else if  (capsense[1] > 100) {
    frequency = 587;
    CircuitPlayground.setPixelColor(1, 0, 0, 255);
  } else if  (capsense[2] > 100) {
    frequency = 659;
    CircuitPlayground.setPixelColor(3, 138, 43, 226);
  } else if  (capsense[3] > 100) {
    frequency = 698;
    CircuitPlayground.setPixelColor(4, 216, 191, 216);
  } else if  (capsense[4] > 100) {
    frequency = 784;
    CircuitPlayground.setPixelColor(5, 238, 130, 238);
  } else if  (capsense[5] > 100) {
    frequency = 880;
    CircuitPlayground.setPixelColor(6, 0, 191, 255);
  } else if  (capsense[6] > 100) {
    frequency = 988;
    CircuitPlayground.setPixelColor(8, 199, 21, 133);
  } else if  (capsense[7] > 100) {
    frequency = 1046;
    CircuitPlayground.setPixelColor(9, 138, 43, 226);
  }
  delay(10);
  CircuitPlayground.clearPixels();
  CircuitPlayground.playTone(frequency, 200); // also plays a tone for a brief amount of time
}
