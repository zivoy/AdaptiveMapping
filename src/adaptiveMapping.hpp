/*
  adaptiveMapping.hpp - Library for doing mapping dynamically.
  Written by Ziv Shalit, Nov 2022.
  Released into the public domain.
*/

template<uint8_t Size>
AdaptiveMapping<Size>::AdaptiveMapping(const unsigned long lifeSpan) {
  _lifeSpan = lifeSpan;

  memset(_minimumQueue, 0, Size * sizeof(History));
  memset(_maximumQueue, 0, Size * sizeof(History));
}

template<uint8_t Size>
long AdaptiveMapping<Size>::maximum() {
  return _maximum.val;
}
template<uint8_t Size>
long AdaptiveMapping<Size>::minimum() {
  return _minimum.val;
}

template<uint8_t Size>
long AdaptiveMapping<Size>::map(long val, long min, long max) {
  read(val);
  if (_minimum.val == _maximum.val) return max;
  return ((val - _minimum.val) * (max - min) / (_maximum.val - _minimum.val)) + min;
}

// update the ranges
template<uint8_t Size>
void AdaptiveMapping<Size>::read(long val) {
  unsigned long currTime = millis();
  // purge older smaller/bigger values
  purge(val, currTime);

  // insert value into options
  // add new elements to end, since thats where the oldest smallest are
  _minimumQueue[Size - 1].val = val;
  _minimumQueue[Size - 1].timeSet = currTime;

  _maximumQueue[Size - 1].val = val;
  _maximumQueue[Size - 1].timeSet = currTime;

  //sort to move purged values to end
  sort();

  // update min and max
  if ((currTime - _maximum.timeSet) > _lifeSpan) {
    if (_maximumQueue[0].timeSet == 0) {
      _maximum.val = val - 1;  //make it get caught in the next section
    } else {
      _maximum.val = _maximumQueue[0].val;
      _maximum.timeSet = _maximumQueue[0].timeSet;
    }
  }
  if ((currTime - _minimum.timeSet) > _lifeSpan) {
      if (_minimumQueue[0].timeSet == 0) {
        _minimum.val = val + 1;  //make it get caught in the next section
      } else {
        _minimum.val = _minimumQueue[0].val;
        _minimum.timeSet = _minimumQueue[0].timeSet;
      }
    }


  if (val > _maximum.val) {
    _maximum.timeSet = currTime;
    _maximum.val = val;
  }

  if (val < _minimum.val) {
    _minimum.timeSet = currTime;
    _minimum.val = val;
  }
}

template<uint8_t Size>
void AdaptiveMapping<Size>::purge(long val, unsigned long currTime) {
  for (int i = 0; i < Size - 1; i++) {
    if (_minimumQueue[i].timeSet != 0 && (_minimumQueue[i].val > val || (currTime - _minimumQueue[i].timeSet) > _lifeSpan)) {
      _minimumQueue[i].timeSet = 0;  // let it be purged
    }

    // if its not purged already and the current value is bigger then it and its newer then it, or it expired
    if (_maximumQueue[i].timeSet != 0 && (_maximumQueue[i].val < val || (currTime - _minimumQueue[i].timeSet) > _lifeSpan)) {
      _maximumQueue[i].timeSet = 0;  // purged it
    }
  }
}

template<uint8_t Size>
void AdaptiveMapping<Size>::sort() {
  bool sortMin = true;
  bool sortMax = true;
  bool sortedMin = false;
  bool sortedMax = false;
  while (sortMin || sortMax) {
    for (int i = 0; i < (Size - 1); i++) {
      // sort min queue
      if (sortMin && smallerThen(_minimumQueue, i + 1, i)) {
        sortedMin = true;
        swap(_minimumQueue, i, i + 1);
      }
      // sort max queue

      if (sortMax && smallerThen(_maximumQueue, i + 1, i)) {
        sortedMax = true;
        swap(_maximumQueue, i, i + 1);
      }

      if (i == (Size - 2)) {
        if (!sortedMin) sortMin = false;
        if (!sortedMax) sortMax = false;
        sortedMin = false;
        sortedMax = false;
      }
    }
  }
}

template<uint8_t Size>
bool AdaptiveMapping<Size>::smallerThen(History *list, uint8_t element1, uint8_t element2) {
  if (list[element1].timeSet == 0) return false;
  if (list[element2].timeSet == 0) return true;
  return list[element1].timeSet < list[element2].timeSet;
}

template<uint8_t Size>
void AdaptiveMapping<Size>::swap(History *list, uint8_t element1, uint8_t element2) {
  History temp = list[element1];
  list[element1] = list[element2];
  list[element2] = temp;
}
