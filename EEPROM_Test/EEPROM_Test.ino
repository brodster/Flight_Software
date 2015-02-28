/**
* EEPROM save state test
* Saves a value into eeprom if none is there
* resetting arduino makes load the state from previously
**/
#include <EEPROM.h>

int addr = 0;
byte val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //clear function
  EEPROM.write(addr, 0);
}

void loop() 
{
//  //Read current value from EEPROM
//  val = EEPROM.read(addr);
//  
//  Serial.print("Value was ");
//  Serial.print(val);
//  val = val+1;
//  
//  Serial.print(", Newly saving ");
//  Serial.print(val);
//  Serial.println();
//  
//  EEPROM.write(addr,val);
//  
//  delay(1000);
}
