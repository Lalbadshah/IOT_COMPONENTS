void setup()
{
  pinMode(13, OUTPUT);
}
void loop()
{
  digitalWrite(13, HIGH);
  delay(200);/*time in ms*/
  digitalWrite(13, LOW);
  delay(200);
}
