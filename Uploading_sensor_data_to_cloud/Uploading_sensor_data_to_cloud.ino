#include "SoftwareSerial.h"

#define DEBUG true

#include <stdlib.h>

// replace with your channel's thingspeak API key
String apiKey = "YRFVOK1QFDA6SKYM";
SoftwareSerial esp(2, 3);



void setup() {
  

  //Setup For sensors
 
  pinMode(A0,INPUT);
  
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  esp.begin(9600);


  //Connect to internet
String cmd;
  int i=1;
while(i!=0)
{if (esp.available())       //Check if Hardware serial monitor is available to take data 
    Serial.write(esp.read());//If esp8266 (wifi Mod) is available then read data from it
  if (Serial.available())         //Check if Software serial monitor is available 
    esp.write(Serial.read());//Hardware serial writes to software serial
    Serial.write("\nConnected?\n");
    delay(5000);
    i=int(Serial.read());
  
  }

  







}

int potentiometer;
String s1;
void loop() {
  // put your main code here, to run repeatedly:

potentiometer = analogRead(A0);

s1= String(potentiometer);

// TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  esp.println(cmd);
  Serial.println(cmd);
   
  if(esp.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;

// prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
 
  getStr +="&field1=";
  getStr += String(s1);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  esp.println(cmd);
  Serial.println(cmd);

  if(esp.find(">")){
    esp.print(getStr);
    Serial.print(getStr);
  }
  else{
    esp.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
    
  // thingspeak needs 15 sec delay between updates
  delay(15000);


  

}
}


