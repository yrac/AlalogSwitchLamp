// #include <main.cpp>
// #include <Ubidots.h>

// const char* UBIDOTS_TOKEN = "BBFF-kMyEA6VX6t7s8WoRgB127VcxCTFk6v";

// Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

// void SendUbi(){

// if(WiFi.status()== WL_CONNECTED){
//     ubidots.add("FanSpeed", speed);// Change for your variable name  
//     ubidots.add("FanRunTime", FanRun);

//     ubidots.add("DateHH", HH);
//     ubidots.add("DateMM", MM);
//     ubidots.add("DateSS", ss);

//     ubidots.add("OnHour", OnHour);
//     ubidots.add("OnMinutes", OnMinutes);
//     ubidots.add("OffHour", OffHour);
//     ubidots.add("OffMinutes", OffMinutes);

//     ubidots.add("FiredOn", FiredOn);
//     ubidots.add("FiredOff", FiredOff);

//     ubidots.add("Temp", temperature);

//     bool bufferSent = false;
//     bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

//     if (bufferSent) {
//     // Do something if values were sent properly
//     Serial.println("Ubi sent by the device");
//     }
//   }
