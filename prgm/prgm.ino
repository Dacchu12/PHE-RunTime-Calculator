const int analogPin = A0; // Analog pin to measure voltage
const int threshold = 0; // Set your threshold voltage (adjust as needed)
unsigned long startTime = 0;
unsigned long totalRunTime = 0;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h> 

WiFiClient client;
HTTPClient http;
String url;
String API ="APG5W9L19542PG7T";
String FieldNo="1";

void ConnecTOWifi(void);

void setup()
{
   Serial.begin(115200);
   ConnecTOWifi();
}
int httpcode;

/*void loop()
{ 
   stepvalue = analogread(A0);//0-1024
   SendGETRequest(stepvalue);
   delay(16000);//16seconds delay
}*/
// https://api.thingspeak.com/update?api_key=APG5W9L19542PG7T&field1=0
//https://maker.ifttt.com/trigger/Runtime/json/with/key/dJ2t-wrv1CM3A_3FW7haxz


void sendGETRequest(int data)
{

    url="http://api.thingspeak.com/update?api_key=";
    url=url+API;
    url=url+"&field";
    url=url+FieldNo;
    url=url+"=";
    url=url+data;
    http.begin(client,url);
    Serial.println("Waiting For Response");
    httpcode=http.GET();
    if(httpcode>0)
   {
    // Serial.print(stepvalue);
   Serial.println("-Data sent successfully");
   }
   else
   {
     Serial.println("Error in sending");
   }
   http.end();
}
void ConnecTOWifi()
{
   WiFi.mode (WIFI_STA); // nodemcu as station
   WiFi.begin("Darshan","12345678");
   Serial.print("connecting to wifi");
   while(WiFi.status() != WL_CONNECTED)
   {
    Serial.print('.');
    delay(200);
   }
   Serial.print ("IP Address:");
   Serial.println(WiFi.localIP());
   Serial.print("MacAddress:");
   Serial.println(WiFi.macAddress());
}

void loop() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC value to voltage

  if (voltage > threshold) {
    // Start the timer
    if (startTime == 0) {
      startTime = millis();
      Serial.println("Motor started.");
    }
  }

  if (voltage <= threshold && startTime != 0) {
    // Stop the timer
    unsigned long runTime = millis();
    runTime = runTime - startTime;
    totalRunTime += runTime; // Update total run time
    totalRunTime=((totalRunTime/1000)/60);
    sendGETRequest(totalRunTime);
    
    Serial.print("Motor ran for ");
    Serial.print(runTime / 3600000UL); // Convert milliseconds to hours
    Serial.println(" hours.");
    startTime = 0; // Reset timer to zero*/
  }
  

  if (totalRunTime >= 1116000000UL)
   { // 310 hours or more
    Serial.println("Final alert: 310 hours reached!");
    totalRunTime = 0; // Reset total run time
  }
//sendGETRequest(totalRunTime);
  
}

