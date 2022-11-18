/*
  AdaptiveMapping - Library for doing mapping dynamically.
  Written by Ziv Shalit, Nov 2022.
  Released into the public domain.
*/

#include <AdaptiveMapping.h>

#define potPin A0

// hold for a minute before dumping maximum
AdaptiveMapping<5> m(60000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // make 0 always be the min
  m.read(0);

  int v = analogRead(potPin);
  // map the input to a range of 0 to a 100
  Serial.println(m.map(v, 0, 100));

  // add delay so its easier to read the console
  delay(5);
}
