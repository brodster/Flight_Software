/*
* ---Team Tomahalk Payload Flight Sloftware---
* File contains the core flight software loop
*/


#include <Wire.h>

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
unsigned long previousTransmitTime=0;



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setup for Adafruit 10DoF IMU
    Wire.begin();
    //initilize_HMC588L_MAGNETOMETER();
    initilize_Adafruit_10_DOF_Sensors();
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
  float sensor_data[5] = {1.0,2.1,3.5,4.3,5.2};
  
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
    transmitData(currentMillis, sensor_data,sizeof(sensor_data)/sizeof(float));
    //Calibrate time to transmit next interval step
    previousTransmitTime = currentMillis - currentMillis%transmitInterval;
  }
  
}

/**
* Collection of the state-specific funcions
* includes: state actions as well as state transition check
**/
//TODO
void launch_wait(float sensor_data[]){
}
void ascent(float sensor_data[]){
}
void rocketDeployment_Stabilization(float sensor_data[]){
}
void seperation(float sensor_data[]){
}
void descent(float sensor_data[]){
}
void landed(){
}



/**
* Required: 
* MISSION_TIME,ALT_SENSOR,OUTSIDE_TEMP,
* INSIDE_TEMP,VOLTAGE,FSW_STATE,angle of descent
*
* Transmission format:
* Transmission 1: 1,2,3,45,6,123,55,3,22,454
* Transmission 2: 33,11,244,55,22,44,222,44
* ie. ',' delimintes new value, '\n' deliminates new transmission
**/
//Fix to include sensors when setup
void transmitData (unsigned long currentMillis, float sensor_data[], int sensor_data_length)
{
  const char delim = ',';
  //transmit mission time in seconds
  Serial.print(currentMillis/1000.0,2);
    
  //transmit sensor data
  //TODO to change for new sensor data format
  for(int i=0; i<sensor_data_length;i++)
  {
    Serial.print(delim);
    Serial.print(sensor_data[i]);
  }
  
  //end transmition
  Serial.println();
}
