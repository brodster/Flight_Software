const int tempPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float temp = getExtTemp();
  Serial.print(temp,1);
  delay(500);
  
  Serial.println();
}

/**
* The main sensor function
* Returns the external temperature in degrees Celcius to a single decimal place
* Accuracy: +-3/4 degrees
**/
float getExtTemp()
{
  int millivolts = round(analogRead(tempPin)*(5000.0/1023.0)); 
  float temp = (millivolts-500)/10.0;
  return temp;
}
