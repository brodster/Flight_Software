/**
* EEPROM functions
* including CanSat Boot and SaveState
**/
#include <EEPROM.h>


//for Stand-Alone Testing:
//void setup() {
//  // put your setup code here, to run once:
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//}


/**
* Boot Sequence Method
* Loads flight software state from memory
* If no previous state or is landed/end state,
* Clear memory and set state to Launch Wait.
**/
void boot()
{
  int addr = 0;
  byte stateFromMemory = EEPROM.read(addr);
  
  if(stateFromMemory == 5 || stateFromMemory == 0)
  {
    //clear memory
    for (int i = 0; i < 512; i++)
    {
      EEPROM.write(i, 0);
    }
    state = 0;
  }
  else
  {
    //load state from memory
    state = stateFromMemory;
  }
}

/**
* Save the Flight Software state to memory
* currently Saving:
* - Flight State
*/
void saveState()
{
  int addr = 0;
  
  EEPROM.write(addr,state);
}
