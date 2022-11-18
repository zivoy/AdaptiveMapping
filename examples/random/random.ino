/*
  AdaptiveMapping - Library for doing mapping dynamically.
  Written by Ziv Shalit, Nov 2022.
  Released into the public domain.
*/

#include <AdaptiveMapping.h>

// have a history queue size of 5 elements (lowers the reselution of the history) and hold for a second
AdaptiveMapping<5> m(1000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(m.minimum() * 100 / RAND_MAX);
  Serial.print(" ");
  Serial.print(m.maximum() * 100 / RAND_MAX);
  Serial.print(" ");
  
  Serial.println(m.map(rand(), 0, 100));
  
  delay(50);
}
