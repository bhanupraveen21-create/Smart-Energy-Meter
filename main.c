#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"   // <-- Your Blynk Template ID from Blynk app
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxxxxxx"   // <-- Your Blynk Template Name
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxx"   // <-- Your Blynk Device Auth Token

#include "EmonLib.h"   
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>   

LiquidCrystal_I2C lcd(0x27, 20, 4);

EnergyMonitor emon;

#define vCalibration 106.8
#define currCalibration 0.52
BlynkTimer timer;

float kWh = 0;
unsigned long lastmillis = millis();

char auth[] = "xxxxxxxxxxxxxxxx";  // <-- Your Blynk Auth Token
const char *ssid ="xxxxxxxxx";     // <-- Your WiFi name (SSID)
const char *pass= "xxxxxxxxxx";    // <-- Your WiFi password
const char* apiKey = "G4ZYYjDEGDLK";
const char* templateID = "114";
const char* mobileNumber = "+91xxxxxxxxx";// <--Your Mobile Number

const char* var1 = "xxxxxxx";  // <-- SMS Title (Example: "Overload Alert")
const char* var2 = "xxxxxxxxxxxxxxxxxx"; // <-- SMS body line where xxxxxx will be replaced with load value

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

 
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Vrms: ");
 lcd.print(emon.Vrms, 2);
 lcd.print(" V");

 lcd.setCursor(0, 1);
 lcd.print("Irms: ");
 lcd.print(emon.Irms, 4);
 lcd.print(" A");

 lcd.setCursor(0, 2);
 lcd.print("Power: ");
 lcd.print(emon.apparentPower, 4);
 lcd.print(" W");

 lcd.setCursor(0, 3);
 lcd.print("kWh: ");
 lcd.print(kWh, 4);
 lcd.print(" kWh");
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

  lcd.init();
  lcd.backlight();
}

void loop() {
  Blynk.run();
  timer.run();
  myTimerEvent();

  if(emon.apparentPower >= xx){ // <-- Replace xx with overload power limit (e.g., 500)
    sendSMS();
    while(emon.apparentPower > xx){  // <-- Same limit as above
      myTimerEvent();
    }
  }
}
