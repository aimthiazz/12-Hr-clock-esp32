/*
 * 12 hr clock
 * Modified from Original Code
 * Modified by Imthiaz 
 * For GMT timezone is 3600;
 * if you want to add your timezone the following math helps
 * GMT 3600
 * 1 hr from GMT=3600
 * 30 min from GMT=1800
 * example for Indian Standard time
 * 5hr 30 min = (3600*5)+(1800*1) [19800]
 */

int timezone=19800; 

#include <WiFi.h>
#include "time.h"

const char* ssid       = "YOUR SSID";
const char* password   = "YOUR PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = timezone; // timezone 3600 is GMT
const int   daylightOffset_sec = 3600;


String am_pm=String("AM");
void printLocalTime()
{
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  //timeinfo.tm_hour=timeinfo.tm_hour;
  
  am_pm=String("AM");
  if (timeinfo.tm_hour==12)
  {
    am_pm=String("PM");
    }
  if (timeinfo.tm_hour > 12)
  {
    timeinfo.tm_hour=timeinfo.tm_hour-12;
    am_pm=String("PM");
   }
   
  Serial.print(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("  ");
  Serial.println(am_pm);
  

}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  
  delay(1000);
  printLocalTime();
}
