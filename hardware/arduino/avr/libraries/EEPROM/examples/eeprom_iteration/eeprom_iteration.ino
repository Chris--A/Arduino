/***
    eeprom_iteration example.

    A set of example snippets highlighting the
    simplest methods for traversing the EEPROM.

    Running this sketch is not necessary, this is
    simply highlighting certain programming methods.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

#include <EEPROM.h>

unsigned long eememValue EEMEM; //This is used in an example at the bottom of the sketch.
                                //Please see the example sketch using_EEMEM.ino for detailed
                                //usage of variables marked with EEMEM.

void setup() {

  /***
    The first four example loops described here show how to iterate the
  entire EEPROM space. See the examples after these to see how you can
  easily iterate selective regions of the EEPROM.
  ***/

  /***
    Iterate the EEPROM using a for loop.
  ***/

  for (int index = 0 ; index < EEPROM.length() ; index++) {

    //Add one to each cell in the EEPROM
    EEPROM[ index ] += 1;
  }

  /***
    Iterate the EEPROM using a while loop.
  ***/

  int index = 0;

  while (index < EEPROM.length()) {

    //Add one to each cell in the EEPROM
    EEPROM[ index ] += 1;
    index++;
  }

  /***
    Iterate the EEPROM using a do-while loop.
  ***/

  int idx = 0;  //Used 'idx' to avoid name conflict with 'index' above.

  do {

    //Add one to each cell in the EEPROM
    EEPROM[ idx ] += 1;
    idx++;
  } while (idx < EEPROM.length());

  
  /***
    C++11 specific iteration using a ranged for loop.
  ***/
  
  for (auto cell : EEPROM) {
  cell += 1; //Increment the cell contents.
  }
  
  /***
    How to iterate over certain regions of EEPROM space.
  
  Using the provided method EEPROM.iterate() you can specify
  a certain range of values to traverse. You can also use this
  method to iterate variables marked with EEMEM (see the example
  using_EEMEM.ino).
  
  The function has two variations:
  
  EEPROM.iterate( start, length );
  EEPROM.iterate( eemem_Pointer );
  ***/
  
  
  //This example allows iterating over an arbitrary range of bytes.
  for( auto cell : EEPROM.iterate(0, 10)){
    cell += 1; //Increment each cell in the specified range.
  }
  
  //This version will iterate over the bytes used by a variable using EEMEM in its declaration.
  for( auto cell : EEPROM.iterate(&eememValue)){  //eememValue is declared at the top of this sketch.
    cell += 1;
  }
  
  /***
    As the EEPROM system supports reading and writing individual bits,
    you can also iterate over the bits contained in a single byte.
    
    This requires using the subscript operator to access a single byte.
  ***/
  
  //Iterate over the bits contained in the first EEPROM cell ( EEPROM[0] ).
  for( auto bit : EEPROM[0] ){
    
    //Set each bit to 1.
    bit = 1; //Other valid values could be true, or HIGH.
  }
  
  
  //Using a nested loop, you can iterate over the bits of regions larger than one byte.
  for( auto cell : EEPROM.iterate(&eememValue)){
  
    for( auto bit : cell ){
    
      bit = 1;
    }
  }
  
  
  
} //End of setup function.

void loop() {}