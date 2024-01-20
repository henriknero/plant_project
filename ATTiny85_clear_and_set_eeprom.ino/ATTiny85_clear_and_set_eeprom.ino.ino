#include <EEPROM.h>
#include "SoftwareSerial.h"
#include "tinysnore.h"
SoftwareSerial SoftSerial(3,4);

byte value = 0;
int logAddress = 0;

void setup() {
  SoftSerial.begin(9600);
  SoftSerial.println("Setup done");
  writeIntIntoEEPROM(0,3);
  for (int address=0; address < EEPROM.length(); address++){
    value = EEPROM.read(address);
    SoftSerial.print(address);
    SoftSerial.print("\t");
    SoftSerial.print(value, DEC);
    SoftSerial.println();
  }
  SoftSerial.println(readIntFromEEPROM(0));
}

void loop() {

}

void writeIntIntoEEPROM(int address, int number)
{ 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}