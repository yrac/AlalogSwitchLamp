#include <Time.h>
#include <TimeLib.h>
//#include <Timezone.h>
#include <NTPClient.h>
#include <helper/Common.h>
#include <services/WifiServices.h>
#include <sunset.h>
#include <EEPROM.h>
#include<string.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDREss  "pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)
#define Latitude  -6.267882
#define Longitude  106.761795
#define TimeZone  7

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
bool needupdate = false, force = false;
//int slottime = 0123456789;

SunSet sun;

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

extern String StateTime, StateDate, LastUpdate ;


//void SavedTime(int slot, String variable){
//  for(int i = 0; i < variable.length(); i++){
//    EEPROM.write(slot + i, variable[i]);
//  }
//  EEPROM.commit();
//}


void ProcedEpochTime(){

  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;

  HH = ptm->tm_hour;
  MM = ptm->tm_min;
  ss = ptm->tm_sec;

  StateDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

  sun.setPosition(Latitude, Longitude, TimeZone);
  sun.setCurrentDate(currentYear, currentMonth, monthDay);

  double sunset = sun.calcSunset();
  double sunrise = sun.calcSunrise();

  int Hset = sunset / 60;
  int Mset = sunset / 60;
  int Hrise = sunrise / 60;
  int Mrise = sunrise / 6;

  if(Hset > 24)
      Hset =  Hset / 6;
  if(Mset >= 60)
      Mset =  Mset / 6;
  if(Hrise > 24)
      Hrise =  Hrise / 6;
  if(Mrise >= 60)
      Mrise =  Mrise / 6;

  OnHour = Hset;
  OnMinutes = Mset;
  OffHour = Hrise;
  OffMinutes = Mrise;
  //char savedvalue[] = String(HH) +""+ String(MM) +""+ String(ss) +""+ String(Hset) +""+ String(Mset) +""+ String(Hrise) +""+ String(Mrise);
  //for(int i = 0; i< sizeof(savedvalue); i++){
  //  SavedTime(i, savedvalue[i]);
  //}


  StateTime = String(HH) +":"+ MM +":"+ ss;
  Serial.println("----------------------------");
  Serial.println("Current Date : "+ StateDate);
  Serial.println("Current Time : "+ StateTime);
  Serial.println("----------------------------");

  Serial.println("SunSet : "+  String(OnHour) +" : "+ String(OnMinutes));
  Serial.println("SunRise : "+ String(OffHour) +" : "+ String(OffMinutes));
}

void UpdateTime(){
  if(CheckConnection()){
    Serial.print("Woke up and update time");
    timeClient.begin();
    timeClient.setTimeOffset(25200);
    delay(5000);
    timeClient.update();

    epochTime = timeClient.getEpochTime();
    ProcedEpochTime();
    LastUpdate =  StateDate +" "+ StateTime;
    LastUpdateHours = HH;
    needupdate = false;
    FiringOn = 0;
    force = true;
  }else if(LastUpdateHours == 0){
    for(int i = 14; i >= 0; i--){
        if(i<2){}
    }
  }else{
   needupdate = true;
  }
}

void GetUpdateTime(){
    bool thru = false;

    if(HH % IntervalUpdate == 0 && HH != LastUpdateHours) thru = true;
    if(needupdate) thru = true;

    if(thru){
      UpdateTime();
      State = "Update Time";
    }
  }

void RunTime(){
  epochTime++;
  ProcedEpochTime();
  SetLightDay(ToMilis(HH, MM), ToMilis(OffHour, OffMinutes), ToMilis(OnHour, OnMinutes));
  force = false;
}

//int ReadTime(int slot){
//  int res;
//  for(int i = 0; i < value.length(); i++){
//    res += int(char(EEPROM.read(slot + i)));
//  }
//  return res;
//}
