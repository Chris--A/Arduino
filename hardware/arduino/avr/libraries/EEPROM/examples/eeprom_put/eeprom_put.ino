/***
    EEPROM put.
    Written by Christopher Andrews
    
    This shows how to use the EEPROM.put() method.
    Also, this sketch will pre-set the EEPROM data for the 
    example sketch eeprom_get.
    
    Note, unlike the single byte version EEPROM.write(),
    the put method will use update semantics. As in a byte
    will only be written to the EEPROM if the data is actually
    different.

***/

#include <EEPROM.h>

void setup(){

  Serial.begin(9600);
  
  float f = 123.456f;  //Variable to store in EEPROM.
  int eeAddress = 0;   //Location we want the data to be put.
  
  
  //One simple call, with the address first and the object second.
  EEPROM.put( eeAddress, f );
  
  Serial.println("Written float data type!");
  
  /*** 
    Get can be used with custom structures too. 
    I have separated this into an extra function.
  ***/
  
  struct MyObject{
    float field1;
    byte field2;
    char name[10];
  };
  
  //Data to store.
  MyObject customVar = {
    3.14f,
    65,
    "Working!"
  };

  eeAddress += sizeof(float); //Move address to the next byte after float 'f'.
  
  EEPROM.put( eeAddress, customVar );
  Serial.print("Written custom data type! \n\nRun the example sketch eeprom_get to see how to retrieve the values!");
}

void loop(){ /* Empty loop */ }