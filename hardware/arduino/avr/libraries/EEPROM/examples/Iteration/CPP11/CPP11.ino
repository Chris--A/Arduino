/***
    A tiny example showing a C++11 
    ranged loop being used to iterate
    the EEPROM cells.
    
    Please note C++11 is not enabled by default in any IDE version yet.
***/

#include <EEPROM.h>

void setup() {

  //Iterate the EEPROM.
  for( auto cell : EEPROM ){

    //Add one to each cell in the EEPROM
    cell += 1;
  }
}

void loop(){}