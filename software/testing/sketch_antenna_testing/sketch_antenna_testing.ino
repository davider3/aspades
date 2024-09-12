void setup() {
  pinMode(A0, INPUT);
  Serial.begin(80000000);
}

void loop() {
  Serial.println(analogRead(A0));  
}
