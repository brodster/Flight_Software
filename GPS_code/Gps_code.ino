#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);    // oR  HardwareSerial mySerial = Serial1;
Adafruit_GPS GPS(&mySerial);

#define GPSECHO  true   // to turn off echoing
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup()  
{
  Serial.begin(9600);
  GPS.begin(9600); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY); / uncomment this line to turn on only the "minimum recommended" data  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  //delay(1000);
  //mySerial.println(PMTK_Q_RELEASE);
}


SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0                                                                                                                                                  99bbb66666666666ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
  GPSECHO;
    //if (c) UDR0 = c;  
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()               
{
  if (! usingInterrupt) {
    char c = GPS.read();
    GPSECHO;
      //if (c) 
      //Serial.print(c);
  }
  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  
  if (timer > millis()) 
  timer = millis();

  if (millis() - timer > 1000) { 
    timer = millis(); 
   // Serial.print(GPS.hour, DEC); Serial.print(':');Serial.print(GPS.minute, DEC); Serial.print(':');Serial.print(GPS.seconds, DEC); Serial.print('.'); Serial.println(GPS.milliseconds); Serial.print("Date: ");
   // Serial.print(GPS.day, DEC); Serial.print('/');Serial.print(GPS.month, DEC); Serial.print("/20");Serial.println(GPS.year, DEC);
    //Serial.print("Fix: "); Serial.print((int)GPS.fix);
    //Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
     // Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);Serial.print(", "); Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.println(GPS.latitudeDegrees, 4);
      Serial.println(GPS.longitudeDegrees, 4);
      
      //Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.println(GPS.angle);
       Serial.println(GPS.altitude);
      //Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
   
  }
}
