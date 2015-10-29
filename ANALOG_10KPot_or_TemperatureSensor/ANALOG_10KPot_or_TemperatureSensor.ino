void setup() {
  Serial.begin(9600);//9600 is BODRATE
}
int sensorValue;
void loop() {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(1000);
//OPEN serial monitor "Ctrl+Shift+M"
}
