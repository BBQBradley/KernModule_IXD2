volatile byte state1 = LOW;
volatile byte state2 = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(3), buttonISR, CHANGE);
}

void buttonISR() {
  state1 = !state1;
  state2 = !state2;
}

void loop() 
{
    digitalWrite(4, state1);
    digitalWrite(5, state2);
}
