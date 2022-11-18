/*
adaptiveMapping - Library for doing mapping dynamically.
Written by Ziv Shalit, Nov 2022.
Released into the public domain.
*/

#include "adaptiveMapping.h"

// hold values for 5 seconds
AdaptiveMapping<> m(5000);

void setup() {
  Serial.begin(9600);
}

int v;
void loop() {
  // increase value
  v = (v + 5) % 100;
  // print the mapped value, the raw value, the minimum and the maximum
  printStuff();
  delay(50);
}

void printStuff() {
  // map the value to a range of 10 to 20
  Serial.print(m.map(v, 10, 20));
  Serial.print(" ");
  Serial.print(v);
  Serial.print(" ");
  Serial.print(m.minimum());
  Serial.print(" ");
  Serial.println(m.maximum());
}