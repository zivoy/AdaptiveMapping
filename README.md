# Adaptive Mapping Arduino library
### A library that makes it easier to map ranges dynamically
This library is good for installations that you can leave and have the sensors always have a reasonable range without needing to calibrate every so often manually

## Usage
```Arduino
AdaptiveMapping<QueueSize> mapName(DataLifeTime);

mapName.map(value, mapToMin, mapToMax);
```
The QueueSize defaults to 11, which is more than enough for most cases, so you can leave it empty. The DataLifeTime is the time (in milliseconds)
it should hold the values before they expire. Change this depending on your use case, a small project might only need a couple of seconds or minutes, but an installation might need it to be in the hours.

Call the map function on the object, passing it the value and the min and max you would like to map the range too.

see [sample.ino](https://github.com/zivoy/AdaptiveMapping/blob/master/examples/sample/sample.ino) example for a full implementation.
