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
    </style>
</head>

<body>
    <h2>Auto Analog Lamp</h2>
    <p>
        <i class="far fa-clock" style="color:#5e6dd7;"></i>
        <span class="dht-labels">Time</span>
        <span id="clock">%CLOCK%</span>
    </p><p>
        <i class="fas fa-thermometer-half" style="color:#5e6dd7;"></i>
        <span class="dht-labels">Temperature</span>
        <span id="temperature">%TEMPERATURE%</span>
        <sup class="units">&deg;C</sup>
    </p>
    <p>
        <i class="fas fa-fan" style="color:#5e6dd7;"></i>
        <span class="dht-labels">Fan</span>
        <span id="fan">%FAN%</span>
        <sup class="units">%</sup>
    </p>
    <p>
        <i class="fas fa-drafting-compass" style="color:#5e6dd7;"></i>
        <span class="dht-labels">Servo</span>
        <span id="servo">%SERVO%</span>
        <sup class="units">&deg;</sup>
    </p>
    
</body>
<script>
setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.data.Temp;
            document.getElementById("clock").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/getstate", true);
    xhttp.send();
}, 10000);
</script>

</html>)
)rawliteral";