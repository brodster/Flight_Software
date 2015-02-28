/*
---Team Tomahalk Payload Flight Sloftware---
*/

#include <EEPROM.h>

/**
* Flight Software state variable:
* -1 - Uninizialized
*  0 - Launch Wait
*  1 - Ascent
*  2 - Rocket Deployment / Stabilization
*  3 - Seperation
*  4 - Descent (Main Payload Action Stage)
*  5 - Landed 
**/
byte state = -1;

// Transmission variables
//time between
const int transmitInterval = 1000;
//Previous transmit time in milliseconds
unsigned long previousTransmitTime;

void setup() 
{
  // put your setup code here, to run once:

}

/**
* Main Software Loop:
* 1. check boot state
* 2. Collect data from sensors
* 3. Preform State-specific functions (actions and transitions check)
* 4. Save State to memory
* 5. Transmit data
**/
void loop() 
{
  //1. Check boot State
  if(state == -1)
  {
    boot();
  }
  
  //2. Collect data from sensors
  //TODO
  //What format do we want for this??
  int sensor_data[5];
  
  //3. Preform State-specific functions
  switch(state)
  {
    case 0:
	launch_wait(sensor_data);
    case 1:
	ascent(sensor_data);
    case 2:
	rocketDeployment_Stabilization(sensor_data);
    case 3:
	seperation(sensor_data);
    case 4:
	descent(sensor_data);
    case 5:
	landed();
    default:
      boot();
  }
  
  saveState();
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousTransmitTime >= transmitInterval)
  {
    transmitData(currentMillis, sensor_data);
    //Calibrate time to transmit next interval step
    previousTransmitTime = currentMillis - currentMillis%transmitInterval;
  }
  
}

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
* Collection of the state-specific funcions
* includes: state actions as well as state transition check
**/
//TODO
void launch_wait(int sensor_data[]){
}
void ascent(int sensor_data[]){
}
void rocketDeployment_Stabilization(int sensor_data[]){
}
void seperation(int sensor_data[]){
}
void descent(int sensor_data[]){
}
void landed(){
}

/**
* Save the Flight Software state to memory
* currently Saving:
* - Flight State
*/
void saveState(){
  int addr = 0;
  
  EEPROM.write(addr,state);
}

void transmitData (unsigned long currentMillis, int sensor_data[]){
}
