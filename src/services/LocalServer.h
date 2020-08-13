 #include <main.cpp>
 
 WiFiClient client = server.available();
 String request = "";
 String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
 String html_2 = "";
 String html_4 = "</div></body></html>";
    //if (!client)  {  return;  }
void LocalServer(){
    if (client)
    {
          // Read the first line of the request
          request = client.readStringUntil('\r');
      
          Serial.println("request:");
          Serial.println(request);
       
          if       ( request.indexOf("FANON") > 0 )  {  digitalWrite(Fan, speed);    }
          else if  ( request.indexOf("FANOFF") > 0 ) {  digitalWrite(Fan, 0);  ;   }
       
       
          // Get the LED pin status and create the LED status message
          if ( digitalRead(Fan)   >= 200) 
          {
              // the LED is on so the button needs to say turn it off
             html_2 = "<form id='F1' action='FANOFF'><input class='button' type='submit' value='Fan On' ></form><br>";
          }
          else                              
          {
              // the LED is off so the button needs to say turn it on
              html_2 = "<form id='F1' action='FANON'><input class='button' type='submit' value='Fan Off' ></form><br>";
          }
       
       
          client.flush();
       
          client.print( header );
          client.print( html_1 );    
          client.print( html_2 );
          client.print( html_4);
       
          delay(5);
          
         // The client will actually be disconnected when the function returns and 'client' object is detroyed
           
    }
}