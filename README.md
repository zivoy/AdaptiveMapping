# Adaptive Mapping Arduino library
### A library that makes it easier to dynamically map ranges
This library is good for instelations that you can just leave and have the sensors always have a reasonable range without needing to manually calibrate every so often

## Usage
```Arduino
AdaptiveMapping<QueueSize> mapName(DataLifeTime);

mapName.map(value, mapToMin, mapToMax);
```
The QueueSize defualts to 11 and I found that that is more then enough for most cases, so you can leave that empty. The DataLifeTime is the time (in milliseconds)
it should hold the values fro before they expire, change this depending on your use case.

call the map function on the object, passing it the value and the min and max you would like to map the range to.

see [sample.ino](https://github.com/zivoy/AdaptiveMapping/blob/master/examples/sample/sample.ino) example for a full implimentation.
