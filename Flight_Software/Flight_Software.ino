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
  
  if(
  
}

/**
* Boot Sequence Method
* Loads flight software state from memory
* If no previous state found or is landed/end state,
* Set state to Launch Wait.
**/
void boot()
{
  //TODO
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
*//
void saveState(){
  //TODO
}
