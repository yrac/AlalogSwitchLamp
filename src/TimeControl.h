#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <NTPClient.h>
#include <helper/Common.h>
#include <services/WifiServices.h>

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
unsigned long epochTime = 0;
bool needupdate = false;
//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

extern String StateTime, StateDate, LastUpdate ;


void ProcedEpochTime(){

  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;

  HH = ptm->tm_hour;
  MM = ptm->tm_min;
  ss = ptm->tm_sec;  

  StateDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

  StateTime = String(HH) +":"+ MM +":"+ ss;
  Serial.println("----------------------------");
  Serial.println("Current Date : "+ StateDate);
  Serial.println("Current Time : "+ StateTime);
  Serial.println("----------------------------");
}

void UpdateTime(){
  Serial.println(WiFi.status());   
  if(WiFi.status() == WL_CONNECTED){  
    Serial.print("Woke up and update time");
    timeClient.begin(); 
    timeClient.setTimeOffset(25200);  
    delay(5000);
    timeClient.update();
    
    epochTime = timeClient.getEpochTime();
    ProcedEpochTime();    
    LastUpdate =  StateDate +" "+ StateTime;
    needupdate = false;
  }else
  {
   needupdate = true;
  }  
}

void GetUpdateTime(){
    bool thru = false;

    if(HH % IntervalUpdate == 0) thru = true;
    if(needupdate) thru = true;    
    else thru = false;

    if(thru){
      UpdateTime();   
      State = "Update Time";
    }
  }


void RunTime(){
  #pragma region Old
    // ss++;
    // if (ss >= 60)
    // {
    //   int overtime = ss - 60;
    //   ss = overtime > 0 ? overtime : 0;           
    //   MM++;
    // }

    // if (MM >= 60)
    // {
    //   MM = 0;
    //   HH++;
    //   LastUpdateHours++;    
    // }

    // if (HH >= 24)
    // {
    //   HH = 0;
    // }    
#pragma endregion

  epochTime++;
  ProcedEpochTime();
  SetLightDay(ToMilis(HH, MM), ToMilis(OffHour, OffMinutes), ToMilis(OnHour, OnMinutes));
}

