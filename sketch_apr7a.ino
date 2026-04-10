const int pumps[] = {2, 3, 4, 5};
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(pumps[i], OUTPUT);
    digitalWrite(pumps[i], HIGH); 
  }
}
void loop() {
  for (int i = 0; i < 4; i++) {
    controlPump(pumps[i], true);  
    delay(4000);                 
    controlPump(pumps[i], false); 
    delay(4000);                 
  }
}
void controlPump(int pin, bool state) {
  if (state == true) {
    digitalWrite(pin, LOW);  
  } else {
    digitalWrite(pin, HIGH); 
  }
}