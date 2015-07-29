/***
   EEPROM Update method

   Stores values read from analog input 0 into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.

   If a value has not changed in the EEPROM, it is not overwritten
   which would reduce the life span of the EEPROM unnecessarily.

   Released using MIT licence.
 ***/

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int  address = 0;  // As EEPROM sizes are larger than 256 bytes, we 
                   // need to use an int to address the entire EEPROM

/***
  To demonstrate the update feature, a counter is used to provide
  a simple data set for storage. As the range of a byte fits into
  EEPROM sizes neatly, it provides a repeating set of values.
***/
byte coutner = 0;  // Only 0 - 255 (256 values).

void setup() {
  /** Empty setup **/
}

void loop() {

  //Write the data using the update() method.
  EEPROM.update(address, counter);
  
  /***
    The function EEPROM.update(address, value) is equivalent to the following:
  
    if( EEPROM.read(address) != value ){
      EEPROM.write(address, value);
    }
  ***/
  
  //Advance to the next address, and increment the counter.
  address = address + 1;
  
  if( counter == 255 ){
    counter = 0;
  }else{
    counter = counter + 1;
  }

  /***
    Wrapping the EEPROM address.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512b EEPROM storage.
    - Arduino Uno:         1kb  EEPROM storage.
    - Arduino Mega:        4kb  EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors that support EEPROM storage.

  ***/

  if( address == EEPROM.length() ){
    address = 0;
  }

  //Slow things down a bit.
  delay(300);
}
