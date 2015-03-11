buzzer_pin = 8;
void setup (){}

void loop (){
buzzer();
}

//Function is used at the end to make the Buzzer active
void buzzer () {
tone (buzzer_pin, 262);
}
