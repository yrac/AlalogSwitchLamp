#include <Arduino.h>
#include <ESP8266HTTPClient.h>

String serverAddress = "http://ini.ddns.net";
int port = 80;
String gettime = ""+String(HH)+":"+String(MM)+":"+String(ss)+"+07:00";
typedef enum {
    PushState,
    PushEvent
} PushType;

HTTPClient http;

void PushData(PushType Push){
    String URIpostData = "";
    String body = "";
    String payload = "";
    int httpCode = 0;
    String postdata  = "";
    if(WiFi.status() == WL_CONNECTED){
        switch (Push){
            case PushState:
                URIpostData = "/api/esp/PostState";
                body = "{\n    \"StateName\":\"Idle\",\n    \"StateDateTime\":\"2020-08-07T"+gettime+"\",\n    \"CreatedDate\":\"2020-08-11T"+gettime+"\"\n}";
                postdata = URIpostData + body;

                http.begin(serverAddress);
                http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
                httpCode = http.POST(postdata);                             
                break;
            case PushEvent:
                URIpostData = "/api/esp/PostState";
                body = "{\n    \"StateName\":\"Idle\",\n    \"StateDateTime\":\"2020-08-07T"+gettime+"\",\n    \"CreatedDate\":\"2020-08-11T"+gettime+"\"\n}";
                postdata = URIpostData + body;

                http.begin(serverAddress);
                http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
                httpCode = http.POST(postdata);         
                break;  
        }    
        Serial.println(String(httpCode)); 
        payload = http.getString(); 
        Serial.println(payload); 
        http.end(); 
        Serial.println("closing connection");
    }
}