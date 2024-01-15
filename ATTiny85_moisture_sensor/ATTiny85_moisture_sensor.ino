#include "SoftwareSerial.h"
#include "tinysnore.h"
SoftwareSerial SoftSerial(3,4);
void setup() {
  SoftSerial.begin(9600);
  while (!SoftSerial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(2, INPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  // prints title with ending line break
  SoftSerial.println("Setup done");
}

void loop() {
  //int sensorValue = readMoisture();
  snore(5000); //7microAmpere
  delay(5000); //7milliAmpere
  /*SoftSerial.println(sensorValue);
  if(sensorValue > 500){
    digitalWrite(0,HIGH);
    delay(5000);
    digitalWrite(0,LOW);
  }
  */
}

int readMoisture(){
  digitalWrite(1, HIGH);
  delay(50);
  return analogRead(1);
  digitalWrite(1,LOW);
}

//The analog and digital pin numbers are not the same.
//PB3 is analog pin 3, that's why it works.
//PB2 is analog pin 1.
//PB4 is analog pin 2.