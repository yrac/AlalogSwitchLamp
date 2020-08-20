#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!--<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.14.0/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">-->
    <script src="https://kit.fontawesome.com/562a07edfa.js" crossorigin="anonymous"></script>
    <style>
    html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
    }

    h2 {
        font-size: 3.0rem;
    }

    p {
        font-size: 3.0rem;
    }

    .units {
        font-size: 1.2rem;
    }

    .dht-labels {
        font-size: 1.5rem;
        vertical-align: middle;
        padding-bottom: 15px;
    }
    .info{
        font-size: 1.2rem;
    }
    </style>
</head>

<body>
    <h2>Auto Analog Lamp</h2>
   
        <i class="fas fa-plug info" style="color:#5e6dd7;"></i>        
        <span id="runninghours" class="info">%RUNNINGHOURS%</span><span class="info"> Hour(s)</span>
        <span id="runningminutes" class="info">%RUNNINGMINUTES%</span><span class="info"> Minutes(s)</span>
    &nbsp
        <i class="fas fa-broadcast-tower info" style="color:#5e6dd7;"></i>
        <span id="lastupdate" class="info">%LASTUPDATE%</span>
    </br>
        <i class="far fa-calendar-alt info" style="color:#5e6dd7;"></i>
        <span id="date" class="info">%DATE%</span>
    <p>
        <i class="far fa-clock" style="color:#5e6dd7;"></i>
        <span id="clock">%CLOCK%</span>
    </p>
    <p>
        <i class="fas fa-thermometer-half" style="color:#5e6dd7;"></i>
        <span id="temperature">%TEMPERATURE%</span>
        <sup class="units">&deg;C</sup>
    </p>
    <p>
        <i class="fas fa-fan" style="color:#5e6dd7;"></i>
        <span id="fan">%FAN%</span>
        <sup class="units">&#37;</sup>
    </p>
    <p>
        <i class="fas fa-drafting-compass" style="color:#5e6dd7;"></i>
        <span id="servo">%SERVO%</span>
        <sup class="units">&deg;</sup>
    </p>
    <p>
        <i class="fas fa-info" style="color:#5e6dd7;"></i>
        <span id="info">%INFO%</span>
    </p>
    
</body>
<script>
setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var obj =this.responseText;
            var jobj = JSON.parse(obj);
            document.getElementById("temperature").innerHTML = jobj.Temperature;
            document.getElementById("clock").innerHTML = jobj.Clock;
            document.getElementById("date").innerHTML = jobj.Date;
            document.getElementById("fan").innerHTML = jobj.Fan;
            document.getElementById("servo").innerHTML = jobj.Servo;
            document.getElementById("lastupdate").innerHTML = jobj.LastUpdate;
            document.getElementById("runninghours").innerHTML = jobj.RunningHour; 
            document.getElementById("runningminutes").innerHTML = jobj.RunningMinutes;                        
            document.getElementById("info").innerHTML = jobj.Info;                        
        }
    };
    xhttp.open("GET", "/getstate", true);
    xhttp.send();
}, 10000);
</script>

</html>
)rawliteral";