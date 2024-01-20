# plant_project
![Schematics](images/schematic.svg)

## Flashing EEPROM with INIT Values
```
C:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude -CC:\Users\henner\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -pattiny85 -cstk500v1 -PCOM6 -b19200 -u -U eeprom:w:eeprom.hex:i
```

