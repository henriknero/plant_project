/*
  ASCII table

  Prints out byte values in all possible formats:
  - as raw binary values
  - as ASCII-encoded decimal, hex, octal, and binary values

  For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

  The circuit: No external hardware needed.

  created 2006
  by Nicholas Zambetti <http://www.zambetti.com>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ASCIITable
*/
#include "SoftwareSerial.h"
SoftwareSerial SoftSerial(3,4);
void setup() {
  //Initialize serial and wait for port to open:
  SoftSerial.begin(9600);
  while (!SoftSerial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  SoftSerial.println("ASCII Table ~ Character Map");
}

// first visible ASCIIcharacter '!' is number 33:
int thisByte = 33;
// you can also write ASCII characters in single quotes.
// for example, '!' is the same as 33, so you could also use this:
// int thisByte = '!';

void loop() {
  // prints value unaltered, i.e. the raw binary version of the byte.
  // The Serial Monitor interprets all bytes as ASCII, so 33, the first number,
  // will show up as '!'
  SoftSerial.write(thisByte);

  SoftSerial.print(", dec: ");
  // prints value as string as an ASCII-encoded decimal (base 10).
  // Decimal is the default format for Serial.print() and Serial.println(),
  // so no modifier is needed:
  SoftSerial.print(thisByte);
  // But you can declare the modifier for decimal if you want to.
  // this also works if you uncomment it:

  // Serial.print(thisByte, DEC);


  SoftSerial.print(", hex: ");
  // prints value as string in hexadecimal (base 16):
  SoftSerial.print(thisByte, HEX);

  SoftSerial.print(", oct: ");
  // prints value as string in octal (base 8);
  SoftSerial.print(thisByte, OCT);

  SoftSerial.print(", bin: ");
  // prints value as string in binary (base 2) also prints ending line break:
  SoftSerial.println(thisByte, BIN);

  // if printed last visible character '~' or 126, stop:
  if (thisByte == 126) {  // you could also use if (thisByte == '~') {
    // This loop loops forever and does nothing
    while (true) {
      continue;
    }
  }
  // go on to the next character
  thisByte++;
}
