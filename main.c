#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxxxxxx"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxx"

#include "EmonLib.h"   
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

 EnergyMonitor emon;

#define vCalibration 106.8
#define currCalibration 0.52
BlynkTimer timer;


 float kWh = 0;
unsigned long lastmillis = millis();

char auth[] = "VA06GwS0I_tElHt7EULbEbExut43CwyG";
const char *ssid ="xxxxxxxxx";  // Replace with your WiFi name
const char *pass= "xxxxxxxxxx"; //Replace with your WiFi password
const char* apiKey = "G4ZYYjDEGDLK";         
const char* templateID = "114";           
const char* mobileNumber = "+91xxxxxxxxx"; //Replace with your mobile number

const char* var1 = "xxxxxxx";//Replace the with the word 
const char* var2 = "xxxxxxxxxxxxxxxxxx";//replace with the word

void sendSMS() {
 if (WiFi.status() == WL_CONNECTED) {
   WiFiClient client; 
   String apiUrl = "/send_sms?ID=" + String(templateID);
   Serial.print("Connecting to server...");
   if (client.connect("www.circuitdigest.cloud", 80)) { 
     Serial.println("connected!");

    String payload = "{\"mobiles\":\"" + String(mobileNumber) + 
                      "\",\"var1\":\"" + String(var1) + 
                      "\",\"var2\":\"" + String(var2) + "\"}";

    client.println("POST " + apiUrl + " HTTP/1.1");
     client.println("Host: www.circuitdigest.cloud");
     client.println("Authorization: " + String(apiKey));
     client.println("Content-Type: application/json");
     client.println("Content-Length: " + String(payload.length()));
     client.println(); 
     client.println(payload); 
    
     int responseCode = -1; 
     while (client.connected() || client.available()) {
       if (client.available()) {
         String line = client.readStringUntil('\n'); 
         Serial.println(line);
        
        if (line.startsWith("HTTP/")) {
           responseCode = line.substring(9, 12).toInt(); 
           Serial.print("HTTP Response Code: ");
           Serial.println(responseCode);
         }

         if (line == "\r") {
           break;
         }
       }
     }

    if (responseCode == 200) {
       Serial.println("SMS sent successfully!");
     } else {
       Serial.print("Failed to send SMS. Error code: ");
       Serial.println(responseCode);
     }
     client.stop(); 
   } else {
     Serial.println("Connection to server failed!");
   }
 } else {
   Serial.println("WiFi not connected!");
 }
}

 void myTimerEvent() {
 emon.calcVI(20, 2000);

    Serial.print("Vrms: ");
    Serial.print(emon.Vrms, 2);
    Serial.print("V");
    Blynk.virtualWrite(V0, emon.Vrms);

    Serial.print("\tIrms: ");
    Serial.print(emon.Irms, 4);
    Serial.print("A");
    Blynk.virtualWrite(V1, emon.Irms);

    Serial.print("\tPower: ");
    Serial.print(emon.apparentPower, 4);
    Serial.print("W");
    Blynk.virtualWrite(V2, emon.apparentPower);

    Serial.print("\tkWh: ");
    kWh = kWh + emon.apparentPower*(millis()-lastmillis)/3600000000.0;
    Serial.print(kWh, 4);
    Serial.println("kWh");
    lastmillis = millis();
    Blynk.virtualWrite(V3, kWh);
}
 void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("*************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  emon.voltage(35, vCalibration, 1.7); 
  emon.current(34, currCalibration);  

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(5000L, myTimerEvent);
}


void loop() {
  Blynk.run();
  timer.run();
  myTimerEvent();
  if(emon.apparentPower >=xx){  // replace the xx and set a limit
    sendSMS();

    while(emon.apparentPower > xx){ // replace the xx and set a limit 
      myTimerEvent();

    }
  }
  
}
