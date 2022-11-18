/*
  adaptiveMapping.h - Library for doing mapping dynamically.
  Written by Ziv Shalit.
*/

#pragma once
#include <Arduino.h>

struct History {
  long val;
  unsigned long timeSet;
};


template<uint8_t Size = 11>
class AdaptiveMapping {
public:
  AdaptiveMapping(const unsigned long lifeSpan);

  void read(long val);
  long map(long val, long min, long max);

  long maximum();
  long minimum();
private:
  History _minimum;
  History _maximum;

  History _minimumQueue[Size];
  History _maximumQueue[Size];

  unsigned long _lifeSpan;
  void sort();
  void purge(long val, unsigned long time);

  bool smallerThen(History *list, uint8_t element1, uint8_t element2);
  void swap(History *list, uint8_t element1, uint8_t element2);
};

#include "adaptiveMapping.hpp"