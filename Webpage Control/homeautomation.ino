#include "SoftwareSerial.h"
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  pinMode(13,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
   
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
 
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     esp8266.find("pin="); // advance cursor to "pin="
     
     int pinNumber = (esp8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
     pinNumber += (esp8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
     
     switch (pinNumber)
      {
	case 9://
            // digitalWrite(4,LOW);
             digitalWrite(13,HIGH);
            // digitalWrite(6,HIGH);
            // digitalWrite(7,LOW);
             Serial.println("LED IS ON");
             break;
	case 10://
             digitalWrite(5,HIGH);
             //digitalWrite(5,LOW);
            // digitalWrite(6,LOW);
             //digitalWrite(7,HIGH);
             Serial.println("BUZZER IS ON");
		break;
        case 11://forward
             digitalWrite(6,HIGH);
             digitalWrite(7,LOW);
            // digitalWrite(6,HIGH);
             //digitalWrite(7,LOW);
             Serial.println("Forward");
		break;
       case 12://backward
            // digitalWrite(4,LOW);
            // digitalWrite(5,HIGH);
             digitalWrite(6,LOW);
             digitalWrite(7,HIGH);
             Serial.println("Backward");
		break;
       case 13://stop
            digitalWrite(4,LOW);
            digitalWrite(5,LOW);
             digitalWrite(6,LOW);
             digitalWrite(7,LOW);
             Serial.println("Stop");
		break;
	default:
		break;
      }
     //digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin    
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG); // close connection
    }
  }
}
 
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}


