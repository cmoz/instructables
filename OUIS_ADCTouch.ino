/*
* @cmoz
* This example works with the OUIS instructable
* It is for touch inputs
* you can use any touch inputs, but the example is with conductive fabric
* fabrics from tinkertailor.tech
* using the ADCTouch library, and the example has 2 inputs
*/

#include "ADCTouch.h"

#include <Servo.h> // this example connects with a servo for motion as a response
Servo myservo;

int ref0, ref1;
int touchPin1 = A7;
int touchPin2 = A9;
// add more touch inputs here depending on the circuit board you are using 

int val0constrained = 0;

int val0high = 400;
int val0low = 0;

int threshold = 10;
int pos = 0;

void setup()
{
  Serial.begin(9600);

  myservo.attach(12);

  ref0 = ADCTouch.read(touchPin1, 500); 
  ref1 = ADCTouch.read(touchPin2, 500); 
  // add more ref here for additional touch pins, the sleeve tutorial has 7 but more can be added
}

void loop()
{
  int value0 = ADCTouch.read(touchPin1);
  int value1 = ADCTouch.read(touchPin2); 
  // add here for additional touch pins

  value0 -= ref0; 
  value1 -= ref1;

  Serial.print(value0 > threshold);
  Serial.print("\t");

  Serial.print(value1 > threshold);
  Serial.print("\t\t");

  Serial.print(value0);
  Serial.print("\t");

  Serial.println(value1);
 
 myservo.write(0);
  if (value0 > threshold) {

    myservo.write(180);
  }

 delay(100);
}
