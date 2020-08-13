#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <NTPClient.h>
#include <services/WifiServices.h>
#include <helper/Common.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDREss  "pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)


// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDREss, NTP_OFFSET, NTP_INTERVAL);

int HH = 0;
int MM = 0;
int ss = 0;
int mm = 0;
int OnHour = 17;
int OnMinutes = 45;
int OffHour = 5;
int OffMinutes = 30;
int LastUpdateHours = 0;
int IntervalUpdate = 5;

void UpdateTime(){
  WiFi.mode(WIFI_RESUME);
  delay(200);
    if(WiFi.status() == WL_CONNECTED){  
      //Event(true);
      timeClient.begin(); 
      timeClient.setTimeOffset(25200);  
      delay(5000);
      timeClient.update();

      HH = timeClient.getHours();
      MM = timeClient.getMinutes();
      ss = timeClient.getSeconds();  
      //Event(false);
      WiFi.mode(WIFI_OFF);
  }
}

void GetUpdateTime(){
  if(LastUpdateHours >= IntervalUpdate){
    UpdateTime();
    LastUpdateHours = 0;    
    State = "Update Time";
  }
}

void PrintTime(){
  Serial.println("----------------------------");
  Serial.println("Time is : "+ String(HH) +":"+ MM +":"+ ss);
  Serial.println("----------------------------");
}

void RunTime(){
  if(mm >= 1000){
      ss = ss + 1;
      if (ss >= 60)
      {
        ss = 0;
        MM++;
      }

      if (MM >= 60)
      {
        MM = 0;
        HH++;
        LastUpdateHours++;    
      }

      if (HH >= 24)
      {
        HH = 0;
      }    

      SetLightDay(ToMilis(HH, MM), ToMilis(OffHour, OffMinutes), ToMilis(OnHour, OnMinutes));
      mm = 0;
    }
    mm++;
}
