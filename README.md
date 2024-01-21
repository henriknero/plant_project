# plant_project
![Schematics ATTiny85 Moisture Sensor circuit](images/schematic.svg)

## Flashing EEPROM with INIT Values
### Linux
```
/home/john/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude -C/home/john/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -u -U eeprom:w:eeprom.hex:i
```
### Windows
```
C:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -pattiny85 -cstk500v1 -PCOM6 -b19200 -u -U eeprom:w:eeprom.hex:i
```
## Fetching logs from EEPROM
The values will be in same format as eeprom.hex file. Each byte except for the first 2bytes will represent a 0-255 value of how moist the soil is. 
### Linux
```
/home/john/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude -C/home/john/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -pattiny85 -cstk500v1 -P/dev/ttyACM0 -b19200 -u -U eeprom:r:result.hex:i
```
### Windows
```
C:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -pattiny85 -cstk500v1 -PCOM6 -b19200 -u -U eeprom:r:result.hex:i
```

## Future improvements
* Setting watering trigger value from EEPROM to be able to easily program the unit for different moisture levels.
* Setting watering trigger value using button (Not sure I want this.)