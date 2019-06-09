#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define SSID "sarang"     // "SSID-WiFiname" (on this very network esp module will connect itself)
#define PASS "project123"       // "password"
#define IP  "api.thingspeak.com"
String msg ="GET /update?api_key=0ZA0LPRF728IYMWC"; //change it with your key..
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
String latitude ;
String longitude;
TinyGPSPlus gps;
int error;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
void setup(){
   Serial.begin(115200);
   pinMode(8,INPUT);
pinMode(9,OUTPUT);
 pinMode(10,INPUT);
pinMode(11,OUTPUT);
digitalWrite(9,LOW);
  ss.begin(GPSBaud);
  Serial.println("AT");
 delay(5000);
  if(Serial.find("OK")){
     delay(2000);
     Serial.println("in the Ok");
     delay(5000);
    connectWiFi();
    delay(5000);
}}
void loop(){
  start:
  while (ss.available()){
      gps.encode(ss.read());
  if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      longitude=String(gps.location.lng(),6);
      latitude=String(gps.location.lat(),6);
     Serial.print(gps.location.lat(),6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(),6);
     updateTemp();
     alcohal();
    
  //Resend if transmission is not completed 
  if (error==1){
    goto start; 
  }
  delay(100); //Update every 1 hour
    }   
  }
}
void updateTemp(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000); 
  if(Serial.find("Error")){
    return;
  }
  cmd = msg ;
  cmd += "&field1=";
  cmd+=latitude;
  cmd+="&field2=";
  cmd+=longitude;
cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")){
    Serial.print(cmd);
    delay(5000);
  }
  else{
    Serial.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
} 
boolean connectWiFi(){
  Serial.println("in conect wifi");
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  if(Serial.find("OK")){
    Serial.println("connected ");
    delay(2000);
    return true;
  }else{
    Serial.println("Not connected");
    return false;
  }
}
void alcohal()
{
  int i=digitalRead(8);
Serial.println(i);
delay(100);
if(i==0)
{
  digitalWrite(9,HIGH);
}
else
{
  digitalWrite(9,LOW);
}
}




