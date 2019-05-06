# IoT-WaterPump
## Hardware

1.ESP8266

2.Arduino soil-moisture sensor

3.Single channel realy(active High type)

4.GSM to WiFi modem for internet connectivity. 
## Purpose
Automatically water the plantation sensing the moisture level of the soil and turning on/off a water pump via relay.
Also make a http post about the pump status once its changed.

## Use
Currently the code (ESP8266/IoT_Water_Pump/) hits a link every time the pump status is changed from "off" to "on" (or "on" to "off") and make a http post in the server.
The data is then shown in a basic table here: http://iotpump.ahmadsum1.dx.am/ 
this could be useful while debugging/testing.

## Enclosure
Made a enclosure in fusion360 for 3d printing.
3d files are available here https://grabcad.com/library/iot-pump-controller-box-1

## features to be added
Remote control the pump over internet(currently just getting the status).
