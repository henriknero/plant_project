#include <EEPROM.h>
#include "SoftwareSerial.h"
#include "tinysnore.h"
SoftwareSerial SoftSerial(3,4);
unsigned long SECONDS = 1000;
unsigned long MINUTES = SECONDS*60;
unsigned long PUMP_ACTIVE_TIME = 5000;
byte MOISTURE_SENSITIVITY = EEPROM.read(511);

void setup() {
  pinMode(2, INPUT); pinMode(1, OUTPUT); pinMode(0, OUTPUT);
  
  SoftSerial.begin(9600);
  while (!SoftSerial) {;} // wait for serial port to connect. Needed for native USB port only
  SoftSerial.print("Moisture Sensitivity: "); SoftSerial.println(MOISTURE_SENSITIVITY);
}

void loop() {
  byte sensorValue = readMoisture();
  logSensorValue(sensorValue);
  if(sensorValue > MOISTURE_SENSITIVITY)
    runPump();
  delay(60*MINUTES);
  //snore(time); // Use when on battery
}

byte readMoisture(){
  digitalWrite(1, HIGH);
  delay(2500);
  byte sensorValue = analogRead(1) / 3; // Value of Sensor never exceeds 750 (when on 5v). 750/3=250 which is lower than max value of a byte so I can store many days at a time.
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

void logSensorValue(byte sensorValue){
  unsigned int currentLogIndex = readIntFromEEPROM(509);
  if (currentLogIndex >= 509) //Rotate back to index 0 to now overwrite current index and moisture sensitivity value
    currentLogIndex = 0;
  SoftSerial.print(currentLogIndex); SoftSerial.print(": "); SoftSerial.println(sensorValue);
  EEPROM.write(currentLogIndex, sensorValue); //Don't overwrite currentLogIndex in EEPROM
  currentLogIndex++;
  writeIntIntoEEPROM(509, currentLogIndex);
}

void writeIntIntoEEPROM(int address, int number)
{ 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

unsigned int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}