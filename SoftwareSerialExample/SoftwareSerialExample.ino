
#include <SoftwareSerial.h>
/* purpose of using Software serial is so we can defina custom RX AND TX*/

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (mySerial.available())       //Check if Hardware serial monitor is available to take data 
    Serial.write(mySerial.read());//If esp8266 (wifi Mod) is available then read data from it
  if (Serial.available())         //Check if Software serial monitor is available 
    mySerial.write(Serial.read());//Hardware serial writes to software serial
}

