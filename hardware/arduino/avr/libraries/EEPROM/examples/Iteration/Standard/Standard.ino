/***
    A tiny example showing how to traverse the EEPROM.
***/

#include <EEPROM.h>

void setup() {

  //Iterate the EEPROM.
  for( int index = 0 ; index < EEPROM.length() ; ++index ){

    //Add one to each cell in the EEPROM
    EEPROM[ index ] += 1;
  }
}

void loop(){}