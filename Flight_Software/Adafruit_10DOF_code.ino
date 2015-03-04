//THIS CODE IS FOR THE ADAFRUIT 10 DOF SENSOR------
//CHECK BUTTOM FOR FUNCTIONS
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>              
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;  /* Update this with the correct SLP for accurate altitude measurements */

//For Stand-alone testing:
//SENSOR INITILIZATION
//void setup(void)
//{
//  Wire.begin();
//  Serial.begin(9600);
//  //initilize_HMC588L_MAGNETOMETER();
//  initilize_Adafruit_10_DOF_Sensors();
//}
//
//
//void loop (){
// float descent_angle, Heading, Altitude, Temperature, Roll;
// adafruit_function (&descent_angle, &Heading, &Altitude, &Temperature, &Roll);
//}





























//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***********************************************************************************************************************************
//***********************************************************************************************************************************
//ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE
/*--DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS--*/
void  initilize_Adafruit_10_DOF_Sensors()
{
  if(!accel.begin())
  {Serial.println("ERROR accelerometer"); while(1);}
  if(!mag.begin())
  {Serial.println("ERROR mahnetometer"); while(1);}
  if(!bmp.begin())
  { Serial.println("ERROR pressure");while(1);}
}
void adafruit_function (float *descent_angle, float *Heading, float *Altitude, float *Temperature, float *Roll)
{ 
  sensors_event_t accel_event;     sensors_event_t mag_event;
  sensors_event_t bmp_event;       sensors_vec_t   orientation;
     accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation))
  {/* 'orientation' should have valid .roll and .pitch fields *///Serial.print(F("Roll: "));  Serial.print(orientation.roll);Serial.print(orientation.pitch);
   *descent_angle = orientation.pitch;
    *Roll = orientation.roll;}
      mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {  *Heading = orientation.heading;}
      bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  {float Temp;
   bmp.getTemperature(&Temp);
   *Temperature = Temp;
   *Altitude = bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, Temp); 
  }
}

