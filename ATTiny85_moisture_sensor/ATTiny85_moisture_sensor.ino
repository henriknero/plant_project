#include <EEPROM.h>
#include "SoftwareSerial.h"
#include "tinysnore.h"
SoftwareSerial SoftSerial(3,4);
unsigned long SECONDS = 1000;
unsigned long MINUTES = SECONDS*60;
unsigned long PUMP_ACTIVE_TIME = 5000;
byte value = 0;

void setup() {
  SoftSerial.begin(9600);
  while (!SoftSerial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(2, INPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  SoftSerial.println("Setup done");
  for (int address=0; address < EEPROM.length(); address++){
    value = EEPROM.read(address);
    SoftSerial.print(address);
    SoftSerial.print("\t");
    SoftSerial.print(value, DEC);
    SoftSerial.println();
    }
}

void loop() {
  byte sensorValue = readMoisture();
  logSensorValue(sensorValue);
  if(sensorValue > 167){
    runPump();
  }
  sleepForAWhile();
}

byte readMoisture(){
  digitalWrite(1, HIGH);
  delay(2500);
  byte sensorValue = analogRead(1) / 3; // Value of Sensor never exceeds 750. 750/3=250 which is lower than max value of a byte so I can store many days at a time.
  digitalWrite(1, LOW);
  return sensorValue;
  //The analog and digital pin numbers are not the same.
  //PB3 is analog pin 3, that's why it works.
  //PB2 is analog pin 1.
  //PB4 is analog pin 2.
}

void runPump(){
    digitalWrite(0,HIGH);
    delay(PUMP_ACTIVE_TIME);
    digitalWrite(0,LOW);
}

void sleepForAWhile(){
  SoftSerial.println("Starting sleep");
  delay(15*SECONDS);
  SoftSerial.println("Sleep done");
}

void logSensorValue(byte sensorValue){
  int currentLogIndex = readIntFromEEPROM(0);
  SoftSerial.print(currentLogIndex);
  SoftSerial.print(": ");
  SoftSerial.println(sensorValue);
  if (currentLogIndex < 510){ //Stop writing when hitting last EEPROM slot
    EEPROM.write(currentLogIndex, sensorValue); //Don't overwrite currentLogIndex in EEPROM
    currentLogIndex++;
    writeIntIntoEEPROM(0, currentLogIndex);
  }
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