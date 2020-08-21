// #include <FS.h>  
// #include <FirebaseArduino.h>
// //#include <ServoControl.h>
// //#include <FanControl.h>

// #define FIREBASE_HOST "https://automatedanalogswitchlamp.firebaseio.com/"                         // the project name address from firebase id
// #define FIREBASE_AUTH "JdpIhfSrkaVl9QUEVC1UagNacMT5b8E2JUuX2oE2"                    // the secret key generated from firebase


// int FireServo = 0, FireFan = 0;

// extern String StateTime, StateDate, LastUpdate ;
// extern int ServoState, FanRun;

// void InitFireBase(){
//      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
// }


// // void GetFireBase(){
// //     FiringServo( Firebase.getInt("ServoState"));
// //     FanRun = Firebase.getInt("FanState"); 
// // }

// void PostFireBase(){
//     Firebase.pushString("Clock", StateTime);
//     Firebase.pushString("Date", StateDate);
//     Firebase.pushFloat("Temperature", temp);
//     Firebase.pushInt("Fan", speed);
//     Firebase.pushInt("Servo", ServoState);
//     Firebase.pushString("LastUpdate", LastUpdate);
//     Firebase.pushInt("RunningHour", (( millis()/1000 ) / 60 ) / 60);
//     Firebase.pushInt("RunningMinutes", (millis()/1000 ) / 60);
//     Firebase.pushString("Info", State);
// }


// void CheckFireBase(){    
//     //GetFireBase();
//     PostFireBase();
//     if (Firebase.failed()) { 
//         State ="Firebase Failed : " + Firebase.error(); 
//         return; 
//     } 
// }