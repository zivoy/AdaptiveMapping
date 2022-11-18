/*
  AdaptiveMapping - Library for doing mapping dynamically.
  Written by Ziv Shalit, Nov 2022.
  Released into the public domain.
*/

#include <AdaptiveMapping.h>

#define potPin A0

// have a history queue size of 5 elements (lowers the reselution of the history) and hold for a minute
AdaptiveMapping<5> m(60000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(potPin);
  // map the input to a range of 0 to a 100
  Serial.println(m.map(v, 0, 100));

  // add delay so its easier to read the console
  delay(5);
}
