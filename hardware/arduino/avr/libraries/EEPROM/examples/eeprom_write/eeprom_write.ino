/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;

void setup() {
  /** Empty setup. **/
}

void loop() {
  /***
    Need to divide by 4 because analog inputs range from
    0 to 1023 and each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/

  byte value = analogRead(0) / 4;

  /***
    Write the value to the appropriate byte of the EEPROM.
    these values will remain there when the board is
    turned off.
  ***/

  EEPROM.write(address, value);

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduino Duemilanove: 512b EEPROM storage.
    - Arduino Uno:         1kb  EEPROM storage.
    - Arduino Mega:        4kb  EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.

    if(address == EEPROM.length()) {
      address = 0;
    }

    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;

    To prevent this example from looping forever and eventually burning out the
    EEPROM, once the last cell has been written, an infinite loop is used to halt
	the execution.

  ***/

  address = address + 1;

  if(address == EEPROM.length()) {
    while( true ){} //This loop will never end, stopping the example.
  }

  delay(100);
}
