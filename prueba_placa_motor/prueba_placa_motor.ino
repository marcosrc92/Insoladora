// constants won't change. They're used here to set pin numbers:
const int up = 2;     // the number of the pushbutton pin
const int down =  3;      // the number of the LED pin
const int en = 13;


void setup() {
  // initialize the LED pin as an output:
  pinMode(up, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(down, OUTPUT);

    pinMode(en, OUTPUT);
}

void loop() {
  digitalWrite(en, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(en, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 

}
