#include<SoftwareSerial.h> 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 
 
// Set the LCD address to 0x27 for a 16 chars and 2 line display 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//SoftwareSerial mySerial(17, 16); // RX, TX 
char Card_id[13];          
bool stringComplete = false;   
int i=0; 
const int voice1=12; 
const int voice2=11; 
const int voice3=10; 
const int voice4=9; 
const int voice5=8; 
const int voice6=7; 
const int voice7=6; 
const int voice8=5; 
const int buzzer=4; 
void setup() { 
  pinMode(voice1,OUTPUT); 
  pinMode(voice2,OUTPUT); 
  pinMode(voice3,OUTPUT); 
  pinMode(voice4,OUTPUT); 
  pinMode(voice5,OUTPUT); 
  pinMode(voice6,OUTPUT); 
  pinMode(voice7,OUTPUT); 
  pinMode(voice8,OUTPUT); 
  pinMode(buzzer,OUTPUT); 
   
  Serial.begin(9600); 
  lcd.begin(); 
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("*RFID BUS "); 
  lcd.setCursor(0,1); 
  lcd.print("Arrival System "); 
  digitalWrite(voice1,HIGH);  
  digitalWrite(voice2,HIGH);  
  digitalWrite(voice3,HIGH);  
  digitalWrite(voice4,HIGH);  
  digitalWrite(voice5,HIGH);  
  digitalWrite(voice6,HIGH);  
  digitalWrite(voice7,HIGH);  
  digitalWrite(voice8,HIGH);  
  delay(1500); 
  delay(2000); 
    
} 
 
void loop() { 
  digitalWrite(voice1,HIGH);  
  digitalWrite(voice2,HIGH);  
  digitalWrite(voice3,HIGH);  
  digitalWrite(voice4,HIGH);  
  digitalWrite(voice5,HIGH);  
  digitalWrite(voice6,HIGH);  
  digitalWrite(voice7,HIGH);  
  digitalWrite(voice8,HIGH);  
lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("*SHOW RFID "); 
  lcd.setCursor(0,1); 
  lcd.print("CARD FOR BUS *"); 
 
  if (stringComplete) { 
    lcd.clear(); 
    lcd.print(Card_id); 
    Serial.print(Card_id); 
    delay(100); 
    if(strcmp(Card_id,"1300A2DD2F43")==0) 
    { 
      digitalWrite(voice1,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("MGBS BUS"); 
      lcd.setCursor(0,1); 
      lcd.print(""); 
       delay(4000); 
       digitalWrite(voice1,HIGH); 
    } 
    if(strcmp(Card_id,"18004DA07683")==0) 
    { 
       digitalWrite(voice2,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("MEHBOOB NAGAR"); 
      lcd.setCursor(0,1); 
      lcd.print("bus "); 
       delay(4000); 
       digitalWrite(voice2,HIGH); 
       
    } 
 
 
  if(strcmp(Card_id,"4B0078CF8579")==0) 
    { 
      digitalWrite(voice3,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("KURNOOL BUS"); 
      lcd.setCursor(0,1); 
      lcd.print(""); 
       delay(4000); 
       digitalWrite(voice3,HIGH);  
    } 
 
    if(strcmp(Card_id,"1400487E0E2C")==0) 
    { 
      digitalWrite(voice4,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("ANANTAPUR BUS"); 
      lcd.setCursor(0,1); 
      lcd.print(""); 
       delay(4000); 
       digitalWrite(voice4,HIGH); 
       
    } 
  if(strcmp(Card_id,"4B00700AE9D8")==0) 
    { 
      digitalWrite(voice5,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("HINDUPUR BUS"); 
      lcd.setCursor(0,1); 
      lcd.print(""); 
       delay(4000); 
       digitalWrite(voice5,HIGH); 
       
    } 
    
if(strcmp(Card_id,"4B006FE1AF6A")==0) // 7 
    { 
      digitalWrite(voice6,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("dharmavaram "); 
      lcd.setCursor(0,1); 
      lcd.print("BUS"); 
       delay(4000); 
       digitalWrite(voice6,HIGH); 
       
    } 
  if(strcmp(Card_id,"1300A2DD2C40")==0) 
    { 
      digitalWrite(voice7,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("yesvantpur "); 
      lcd.setCursor(0,1); 
      lcd.print("BUS"); 
       delay(4000); 
       digitalWrite(voice7,HIGH); 
       
    } 
     if(strcmp(Card_id,"1300A2DD2D41")==0) 
    { 
      digitalWrite(voice8,LOW); 
       lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("BANGLORE BUS"); 
      lcd.setCursor(0,1); 
      lcd.print(""); 
       delay(4000); 
       digitalWrite(voice8,HIGH); 
       
    } 
    if(strcmp(Card_id,"1700A2DD2C40")==0) 
    { 
      digitalWrite(buzzer,HIGH); 
       lcd.clear();
