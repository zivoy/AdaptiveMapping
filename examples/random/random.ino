/*
  AdaptiveMapping - Library for doing mapping dynamically.
  Written by Ziv Shalit, Nov 2022.
  Released into the public domain.
*/

#include <AdaptiveMapping.h>

AdaptiveMapping<> m(1000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(m.minimum()*100/RAND_MAX);
  Serial.print(" ");
  Serial.print(m.maximum()*100/ RAND_MAX);
  Serial.print(" ");
  
  Serial.println(m.map(rand(), 0, 100));
  delay(50);
}
