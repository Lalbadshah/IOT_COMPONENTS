
#include <SoftwareSerial.h>
 
#define DEBUG true
SoftwareSerial esp8266(2,3);      


#define APIKEY "LBKTS2OCP28G64A1" 

#define TARGET_IP "184.106.153.149"

#define TARGET_PORT "80"        

#define ID "nishant singh"  
#define PASS "nishant123"  

                             
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);
   
      

    sendData("AT+RST\r\n",1000,DEBUG); 
     
    sendData("AT+CWMODE=1\r\n",1000,DEBUG); 
    
      String cmd="AT+CWJAP=\"";  
      cmd+=ID;
      cmd+="\",\"";
      cmd+=PASS;
      cmd+="\"";      
     sendData( cmd+"\r\n",1000,DEBUG); //
    
    
     sendData("AT+CIPMUX=0\r\n",1000,DEBUG); // 
    
}
 
void loop()
{ 

  /////////////////////////////////////////////////////////////////////////
    delay(1000);  //3 seg
    
  //////////////////////////////////////////////////////////////////////
   
  int sensorValue_batt = analogRead(1023);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage_Batt = (sensorValue_batt * (3.37 / 722.0));
   
     
   ///CONVERT  FLOAT TO CHAR  + CHAR TO STRING 
       
   char outstr1[15];
   dtostrf(voltage_Batt,4, 2, outstr1);   //float to char  4 numero de caracteres  3 cifras sin espacio
   String valor1 = outstr1;   // char to string
      
   //  String con tweet
   String  updateTwitterStatus = ("Your pot value is " + valor1 + "Volt");      
      
     
    String webpage = "AT+CIPSTART=\"TCP\",\""; 
    webpage += TARGET_IP;
    webpage += "\",80\r\n";         
    sendData(webpage,1000,DEBUG);        

    // Create HTTP POST Data   
               
    String tsData = "api_key=" APIKEY "&status=" + updateTwitterStatus ;    
     
    String webpage1 = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
    webpage1+="Host: api.thingspeak.com\n";
    webpage1+="Connection: close\n";
    webpage1+="Content-Type: application/x-www-form-urlencoded\n";
    webpage1+="Content-Length: ";
    webpage1+=tsData.length();
    webpage1+="\n\n";
    webpage1+=tsData;
       
     //// envia   comando AT + cantidad de caracteres   
      
     String cipsend = "AT+CIPSEND=";     
     cipsend+= webpage1.length();
     cipsend+="\r\n";     
      
     sendData(cipsend,1000,DEBUG);
     sendData(webpage1,1000,DEBUG);   

      //// comando AT de cierre de conexion            
     sendData("AT+CIPCLOSE=0\r\n",1500,DEBUG);
         

              /// DELAY para reenvio de datos a twitter
     delay(10000);  //3 seg

 
}
 
 
 //// rutina de depuracion via puerto serial
 
  
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
