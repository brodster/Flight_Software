/**
* XBee transmition testing
**/

void setup() {
  Serial.begin(9600);

}

void loop() {
  
    
    for (int testVal = 1;testVal<=10;testVal++)
    {
      Serial.println(testVal);
    }
    delay(1000);
  
}
